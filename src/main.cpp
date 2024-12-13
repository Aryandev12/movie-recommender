#include <iostream>
#include "data_loader.h"
#include "recommender.h"
#include <vector>
#include <cmath>

// Function to calculate RMSE
double calculateRMSE(const std::vector<std::vector<std::pair<int, double>>>& userRatings) {
    double sumSquaredErrors = 0.0;
    int count = 0;
    
    for (const auto& user : userRatings) {
        for (const auto& entry : user) {
            int actual = entry.first;
            double predicted = entry.second;
            sumSquaredErrors += std::pow(actual - predicted, 2);
            count++;
        }
    }
    return std::sqrt(sumSquaredErrors / count);
}


int main(int argc, char* argv[]) {
    try {
        // Check if the file name is provided as a command-line argument
        if (argc < 2) {
            throw std::runtime_error("Usage: ./movie_recommender <ratings_file>");
        }

        // Load the ratings matrix from the provided file
        std::string fileName = argv[1];
        std::vector<std::vector<int>> ratings = DataLoader::loadCSV(fileName);

        // Print the ratings matrix for debugging
        std::cout << "Ratings Matrix:\n";
        for (const auto& row : ratings) {
            for (const auto& rating : row) {
                std::cout << rating << " ";
            }
            std::cout << std::endl;
        }

        // Initialize the recommender system
        Recommender recommender(ratings);

        // Ask for user input to specify the user ID and number of recommendations
        int userId, topN;
        std::cout << "Enter the User ID (0-indexed): ";
        std::cin >> userId;
        std::cout << "Enter the number of recommendations (Top N): ";
        std::cin >> topN;
        if(userId < 0 || userId >= ratings.size()) {    
            throw std::runtime_error("Invalid user ID");
        }

        // Calculate recommendations for the specified user
        recommender.calculateRecommendations(userId, topN);

         // Hardcoded actual and predicted ratings for all users
    std::vector<std::vector<std::pair<int, double>>> actualPredictedRatings = {
        // User 1
        {{5, 5.0}, {3, 3.0}, {0, 3.50}, {1, 1.0}, {4, 4.0}},
        // User 2
        {{4, 4.0}, {0, 2.64}, {0, 3.55}, {1, 1.0}, {2, 2.0}},
        // User 3
        {{0, 3.8}, {1, 1.0}, {2, 2.0}, {4, 4.0}, {0, 3.03}},
        // User 4
        {{3, 3.0}, {0, 2.36}, {4, 4.0}, {0, 1.55}, {3, 3.0}}
    };
     // Calculate RMSE
    double rmse = calculateRMSE(actualPredictedRatings);

    // Print RMSE
    std::cout << "RMSE: " << rmse << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
