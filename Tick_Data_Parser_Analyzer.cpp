
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>

class Tick {
public:
    time_t timeStamp;
    float price, volume;

    void setTimeStamp(std::string x) {
        long long unixTimeStamp = std::stoll(x);
        time_t t = static_cast<time_t>(unixTimeStamp);
        timeStamp = t;

    }

    void setPrice(std::string x) {
        price = std::stof(x);
    }

    void setVolume(std::string x) {
        volume = std::stof(x);
    }

    time_t getTimeStamp() {
        return timeStamp;
    }

    float getPrice(){
        return price;
    }

    float getVolume() {
        return volume;
    }
        
};

std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> result;
    std::string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == '"') {
            // Toggle inQuotes if it's a quote not escaped by another quote
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                field += '"'; // Escaped quote
                ++i;
            }
            else {
                inQuotes = !inQuotes;
            }
        }
        else if (c == ',' && !inQuotes) {
            result.push_back(field); //Inserts into the end of the Vector
            field.clear();
        }
        else {
            field += c;
        }
    }
    result.push_back(field); // Add last field
    return result;
}

// Function to read CSV file into a 2D vector
std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    std::vector<std::vector<std::string>> data;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            data.push_back(parseCSVLine(line));
        }
    }

    file.close();
    return data;
}

std::vector<Tick> gatherTickData(const std::vector<std::vector<std::string>> &csvData) {
    std::vector<Tick> results;
    Tick tempTick;

    for (const auto& row : csvData) {
        tempTick.setTimeStamp(row[0]);
        tempTick.setPrice(row[4]);
        tempTick.setVolume(row[6]);

        results.push_back(tempTick);
    }

    return results;
}

float getMean(std::vector<Tick> results, std::string dataType) {
    float sum;
    sum = 0;


    if (dataType == "Price") {
        for (Tick& record : results) {
            sum =+ record.getPrice();
        }
    }
    else if (dataType == "Volume") {
        for (Tick& record : results) {
            sum =+ record.getVolume();
        }
    }
    else {
        return -1;
    }

    return sum / results.size();

}

float getVariance(std::vector<Tick> results, std::string dataType) {
    float sum, mean, output;

    sum = 0;
    mean = -1;


    mean = getMean(results, dataType);

    if (mean == -1) {
        return -1;
    }

    if (dataType == "Price") {

        for (Tick& record : results) {
            sum += pow((record.getPrice() - mean),2);
        }

    }
    else if (dataType == "Volume") {
        for (Tick& record : results) {
            sum =+ pow((record.getVolume() - mean), 2);
        }
    }
    else {
        return -1;
    }

    output = sum / results.size();
    return output;

}

float getMin(std::vector<Tick> results, std::string dataType) {
    float min;

    if (dataType == "Price") {
        min = results.front().getPrice();

        for (Tick& record : results) {
            if (record.getPrice() < min) {
                min = record.getPrice();
            }
        }
    }
    else if (dataType == "Volume") {
        min = results.front().getVolume();

        for (Tick& record : results) {
            if (record.getVolume() < min) {
                min = record.getVolume();
            }
        }
    }
    else {
        return -1;
    }

    return min;
}

float getMax(std::vector<Tick> results, std::string dataType) {
    float max;

    if (dataType == "Price") {
        max = results.front().getPrice();

        for (Tick& record : results) {
            if (record.getPrice() > max) {
                max = record.getPrice();
            }
        }
    }
    else if (dataType == "Volume") {
        max = results.front().getVolume();

        for (Tick& record : results) {
            if (record.getVolume() > max) {
                max = record.getVolume();
            }
        }
    }
    else {
        return -1;
    }

    return max;
}

void statistics(std::vector<Tick> results, std::string dataType) {

    float mean, variance, min, max;
    
    if (dataType == "Price" || dataType == "Volume") {
        mean = getMean(results, dataType);
        variance = getVariance(results, dataType);
        min = getMin(results, dataType);
        max = getMax(results, dataType);

        std::cout << dataType << " Statistics: Mean = " << mean << ", Variance = " << variance << ", Min = " << min << ", Max = " << max << std::endl;

    }
    else {
        return;
    }


}



int main()
{
    try {
        auto start = std::chrono::high_resolution_clock::now();
        std::string filename;
        std::vector<Tick> results;
        float mean, variance, min, max;

        filename = "..../Tick_Data_Parser_Analyzer/FX_EURUSD_60.csv";

        std::vector<std::vector<std::string>> csvData = readCSV(filename);

        results = gatherTickData(csvData);

        statistics(results, "Price");
        statistics(results, "Volume");

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Runtime: " << elapsed.count() << " seconds\n";
        
        
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}

//time,open,high,low,close,Volume,K,D,ATR

