#ifndef POSTOFFICE_H
#define POSTOFFICE_H

#include "./../interfaces/ipostoffice.h"
#include "./../headers/Client.h"

#include <memory>
#include <vector>


class PostOffice : public IPostOffice {

public:

    explicit PostOffice(unsigned gate_count);

    ~PostOffice() override;

    std::shared_ptr<IClient> getClient(const std::string& identificationNumber) override;

    void enqueueClient(const std::shared_ptr<IClient>& client) override;

    std::vector<std::string> getStatus() override;

    void gateReady(unsigned gateIndex) override;

    void collectPackages(unsigned gateIndex) override;


private:

    std::vector<std::shared_ptr<IClient>> queue;
    std::vector<std::shared_ptr<IClient>> gates;
    std::vector<std::shared_ptr<IClient>> clients;
    unsigned gateCount;


    void loadFromFile();

    void loadToFile();

    std::string eraseNewLines(std::string str);

};

#endif
