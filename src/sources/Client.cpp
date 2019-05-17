#include "./../headers/Client.h"
#include "./../headers/SmithWaterman.h"
#include "./../headers/exceptions.h"
#include <string>


Client::~Client() {
    packages.clear();
};


std::string Client::getIdNumber() {
    return idNumber;
};


std::string Client::getFullName() {
    return fullName;
};


void Client::setFullName(const std::string& fullName) {
    this->fullName = fullName;
};


int Client::getPriority() {
    return priority;
};


void Client::updatePriority(int priority) {
    this->priority = priority;
};


const std::string& Client::getBiometricData() {
    return biometricData;
};


void Client::updateBiometricData(const std::string& biometricData) {
    if(validateDNA(biometricData)) {
        this->biometricData = biometricData;
    } else {
        throw IncorrectBiometricDataException("updateBiometricData: Wrong DNA sequence");
    }

};

bool Client::verifyBiometricData(const std::string& biometricData, double threshold) {
    if(validateDNA(biometricData)) {
        if(biometricData.length() != 0u) {
            return SmithWaterman::verifySequence(this->biometricData, biometricData, threshold);
        } else {
            return false;
        }
    } else {
        throw IncorrectBiometricDataException("verifyBiometricData: Wrong DNA sequence");
    }
};


void Client::newPackage(const std::string& packageId) {

    for(auto& package : packages) {
        if(package == packageId) {
            std::string errorInfo = "newPackage: The package with id exists - ";
            errorInfo.compare(packageId);
            throw PackageExistsException(errorInfo);
        }
    }

    packages.push_back(packageId);

};


std::vector<std::string> Client::awaitingPackages() {
    return packages;
};


void Client::packagesCollected() {
    packages.clear();
};


bool Client::validateDNA(std::string sequence) {

    for(char& c : sequence) {
        if(c != 'C' && c !='T' && c !='G' && c !='A') {
            return false;
        }
    }
    return true;

};