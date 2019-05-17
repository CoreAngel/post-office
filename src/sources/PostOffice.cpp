#include "./../headers/PostOffice.h"
#include "./../headers/Client.h"
#include "./../headers/exceptions.h"

#include <utility>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>


PostOffice::PostOffice(unsigned gate_count) : gateCount(gate_count) {

    loadFromFile();

    for(unsigned i = 0; i < gateCount; i++) {
        gates.push_back(nullptr);
    }

};


PostOffice::~PostOffice() {

    loadToFile();

    queue.clear();
    gates.clear();
    clients.clear();
};


std::shared_ptr<IPostOffice> IPostOffice::create(unsigned gate_count) {

    if(gate_count > 0) {
        std::shared_ptr<IPostOffice> postOfficePtr(new PostOffice(gate_count));
        return postOfficePtr;
    }

    return nullptr;

};


std::shared_ptr<IClient> PostOffice::getClient(const std::string& identificationNumber){

    for(auto& clientPtr : clients) {

        std::string idString = clientPtr->getIdNumber();
        if(idString == identificationNumber) {
            return clientPtr;
        }

    }

    std::shared_ptr<IClient> newClientPtr(new Client(identificationNumber));
    clients.push_back(newClientPtr);
    return newClientPtr;

};


void PostOffice::enqueueClient(const std::shared_ptr<IClient>& client) {

    bool finded = false;

    for(auto& c : queue) {
        if(c == client) {
            finded = true;
            break;
        }
    }

    if(!finded && !client->getFullName().empty()) {
        for (auto it = queue.begin();; it++) {
            if (queue.end() == it || it->get()->getPriority() < client->getPriority()) {
                queue.insert(it, client);
                break;
            }
        }
    }

};


std::vector<std::string> PostOffice::getStatus() {

    std::vector<std::string> fullNameVector;

    for(auto& client : gates) {

        if(client == nullptr) {
            fullNameVector.emplace_back("");
        } else {
            fullNameVector.push_back(client->getFullName());
        }

    }

    return fullNameVector;

};


void PostOffice::gateReady(unsigned gateIndex) {

    if(gateIndex >= gateCount) {
        throw IncorrectGateException("gateReady: Wrong gate index");
    } else {

        if(!queue.empty()) {
            gates[gateIndex] = queue[0];
            queue.erase(queue.begin());

        } else {
            gates[gateIndex] = nullptr;
        }
    }

};


void PostOffice::collectPackages(unsigned gateIndex) {

    if(gateIndex >= gateCount) {
        throw IncorrectGateException("collectPackages: Wrong gate index");
    } else if(gates[gateIndex] == nullptr) {
        throw IncorrectGateException("collectPackages: There is no client at the gate.");
    } else {
        gates[gateIndex]->packagesCollected();
    }

};


void PostOffice::loadFromFile() {

    std::ifstream file;
    file.open("clients.txt");

    if(file.is_open()) {

        std::shared_ptr<IClient> newClientPtr = nullptr;

        bool packages = false;
        std::string line;
        while (std::getline(file, line))
        {

            if(eraseNewLines(line).empty()) {
                clients.push_back(newClientPtr);
                newClientPtr = nullptr;
                packages = false;
                continue;
            }


            if(!packages) {
                std::string id = eraseNewLines(line);
                newClientPtr = std::shared_ptr<IClient>(new Client(id));

                std::getline(file, line);
                std::string name = eraseNewLines(line);
                newClientPtr->setFullName(name);

                std::getline(file, line);
                std::istringstream iss(line);
                int priority;
                iss >> priority;
                newClientPtr->updatePriority(priority);

                std::getline(file, line);
                std::string biometric = eraseNewLines(line);
                biometric = eraseNewLines(biometric);
                newClientPtr->updateBiometricData(biometric);

                packages = true;
            } else {
                std::string package = eraseNewLines(line);
                package = eraseNewLines(package);
                newClientPtr->newPackage(package);
            }

        }

    }

    file.close();

};



void PostOffice::loadToFile() {

    std::ofstream file;
    file.open("clients.txt");

    if(file.is_open()){

        for(auto& c : clients) {
            file << c->getIdNumber() << "\n";
            file << c->getFullName() << "\n";
            file << c->getPriority() << "\n";
            file << c->getBiometricData() << "\n";

            for(auto& p : c->awaitingPackages()) {
                file << p << "\n";
            }

            file << "\n";

        }

    }

    file.close();

};


std::string PostOffice::eraseNewLines(std::string str) {

    for(auto it = str.begin(); it != str.end(); it++) {

        if(*it == '\n' || *it == '\r') {
            str.erase(it);
        }

    }

    return str;

};