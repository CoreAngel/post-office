# Post office
Simple post office implementation in C++ 11
- Queue management with the possibility of adding priority.</br>
- Biometric verification (simplified Smith-Waterman algorithm)</br>
- Permanent saving of queue status</br>

### Example of use:<br/>

```cpp
try {
        auto post_office = IPostOffice::create(5);

        auto client0 = post_office->getClient("96052791812");
        client0->setFullName("John Smith");
        client0->newPackage("package 1");
        client0->newPackage("package 2");
        client0->newPackage("package 3");

        auto client1 = post_office->getClient("94072743523");
        client1->setFullName("Cade Goldsmith");
        client0->newPackage("package 1");
        client0->newPackage("package 2");
        client1->updatePriority(1);
        client1->updateBiometricData("TGTTGACTA");

        post_office->enqueueClient(client0);
        post_office->enqueueClient(client1);

        std::cout << client1->verifyBiometricData("TGTTACGG", 2.0) << std::endl;

        post_office->gateReady(3);
        post_office->gateReady(4);
        auto status = post_office->getStatus();

        auto packages = client0->awaitingPackages();
        client0->packagesCollected();

    } catch (const IncorrectGateException &e) {
        std::cout << "IncorrectGateException: " << e.what() << std::endl;
    } catch (const PackageExistsException &e) {
        std::cout << "PackageExistsException: " << e.what() << std::endl;
    } catch (IncorrectBiometricDataException &e) {
        std::cout << "IncorrectBiometricDataException: " << e.what() << std::endl;
    }
```