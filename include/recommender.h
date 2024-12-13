#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include <vector>
#include <string>

// Class to calculate movie recommendations
class Recommender {
public:
    Recommender(const std::vector<std::vector<int>>& ratingsMatrix);
    void calculateRecommendations(int userId, int topN);
private:
    std::vector<std::vector<int>> ratingsMatrix;
    std::vector<std::vector<double>> similarityMatrix;
     std::vector<std::vector<double>> userSimilarities;    
    std::vector<double> predictedRatings; 

    void calculateUserSimilarities();
    double computeCosineSimilarity(const std::vector<int>& user1, const std::vector<int>& user2);
    void predictRatings(int userId);
};

#endif 
