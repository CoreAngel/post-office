#ifndef CLIENT_H
#define CLIENT_H

#include "./../interfaces/iclient.h"

#include <vector>
#include <string>


class Client : public IClient {

public:

    explicit Client(std::string id) : idNumber(std::move(id)), priority(0), fullName(""), biometricData("") {};

    ~Client() override;

    std::string getIdNumber() override;

    std::string getFullName() override;

    void setFullName(const std::string& fullName) override;

    int getPriority() override;

    void updatePriority(int priority) override;

    const std::string& getBiometricData() override;

    void updateBiometricData(const std::string& biometricData) override;

    bool verifyBiometricData(const std::string& biometricData, double threshold) override;

    void newPackage(const std::string& packageId) override;

    std::vector<std::string> awaitingPackages() override;

    void packagesCollected() override;


private:

    const std::string idNumber;
    std::string fullName;
    std::string biometricData;
    int priority;
    std::vector<std::string> packages;

    bool validateDNA(std::string sequence);

};

#endif