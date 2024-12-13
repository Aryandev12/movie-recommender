#include "recommender.h"
#include <iostream>
#include <cmath>
#include <algorithm>

// Constructor
Recommender::Recommender(const std::vector<std::vector<int>>& ratingsMatrix) 
    : ratingsMatrix(ratingsMatrix) {}

// Function to calculate user similarities
void Recommender::calculateUserSimilarities() {
    int numUsers = ratingsMatrix.size();
    similarityMatrix.resize(numUsers, std::vector<double>(numUsers, 0.0));

    std::cout << "\n--- Cosine Similarity Calculations ---\n";
    for (int i = 0; i < numUsers; ++i) {
        for (int j = i; j < numUsers; ++j) {
            if (i == j) {
                similarityMatrix[i][j] = 1.0;
            } else {
                double similarity = computeCosineSimilarity(ratingsMatrix[i], ratingsMatrix[j]);
                similarityMatrix[i][j] = similarity;
                similarityMatrix[j][i] = similarity;
                std::cout << "Similarity between User " << i << " and User " << j 
                          << ": " << similarity << "\n";
            }
        }
    }

    std::cout << "\n--- User Similarity Matrix ---\n";
    for (const auto& row : similarityMatrix) {
        for (double sim : row) {
            std::cout << sim << "\t";
        }
        std::cout << "\n";
    }
}

// Function to compute cosine similarity
double Recommender::computeCosineSimilarity(const std::vector<int>& user1, const std::vector<int>& user2) {
    double dotProduct = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (size_t i = 0; i < user1.size(); ++i) {
        dotProduct += user1[i] * user2[i];
        norm1 += user1[i] * user1[i];
        norm2 += user2[i] * user2[i];
    }
    double similarity = norm1 && norm2 ? dotProduct / (std::sqrt(norm1) * std::sqrt(norm2)) : 0.0;
    std::cout << "Computed cosine similarity: " << similarity << "\n"; // Debug
    return similarity;
}

// Function to predict ratings
void Recommender::predictRatings(int userId) {
    predictedRatings.assign(ratingsMatrix[0].size(), 0.0);

    std::cout << "\n--- Predicting Ratings for User " << userId << " ---\n";
    for (size_t movieId = 0; movieId < ratingsMatrix[userId].size(); ++movieId) {
        if (ratingsMatrix[userId][movieId] != 0) continue;

        double weightedSum = 0.0, similaritySum = 0.0;
        for (size_t otherUserId = 0; otherUserId < ratingsMatrix.size(); ++otherUserId) {
            if (userId == otherUserId || ratingsMatrix[otherUserId][movieId] == 0) continue;

            double similarity = similarityMatrix[userId][otherUserId];
            weightedSum += similarity * ratingsMatrix[otherUserId][movieId];
            similaritySum += std::abs(similarity);
        }

        if (similaritySum != 0) {
            predictedRatings[movieId] = weightedSum / similaritySum;
        }

        std::cout << "Movie " << movieId + 1 << ": Predicted rating = " 
                  << predictedRatings[movieId] << "\n";
    }
}

// Function to calculate recommendations
void Recommender::calculateRecommendations(int userId, int topN) {
    std::cout << "\n--- Calculating Recommendations ---\n";
    calculateUserSimilarities();
    predictRatings(userId);

    std::vector<std::pair<int, double>> movieRatings;
    for (size_t movieId = 0; movieId < predictedRatings.size(); ++movieId) {
        if (ratingsMatrix[userId][movieId] == 0) {
            movieRatings.emplace_back(movieId, predictedRatings[movieId]);
        }
    }

    std::cout << "\n--- All Predicted Ratings for Unrated Movies ---\n";
    for (const auto& pair : movieRatings) {
        std::cout << "Movie " << (pair.first + 1) << ": " << pair.second << "\n";
    }

    std::sort(movieRatings.begin(), movieRatings.end(),
              [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
                  return b.second < a.second;
              });

    std::cout << "\n--- Top " << topN << " Recommendations for User " << userId << " ---\n";
    for (int i = 0; i < topN && i < static_cast<int>(movieRatings.size()); ++i) {
        std::cout << "Movie " << (movieRatings[i].first + 1) << " with predicted rating: "
                  << movieRatings[i].second << "\n";
    }
}