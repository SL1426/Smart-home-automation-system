#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Device {
protected:
    string name;
    bool status;
public:
    Device(string deviceName) : name(deviceName), status(false) {}

    virtual string showStatus() const {
        return name + " is " + (status ? "ON" : "OFF");
    }

    virtual void turnOn() {
        status = true;
    }

    virtual void turnOff() {
        status = false;
    }

    virtual ~Device() {}
};

class Light : public Device {
public:
    Light(string lightName) : Device(lightName) {}

    void turnOn() override {
        Device::turnOn();
        cout << name << " is now turned ON.\n";
    }

    void turnOff() override {
        Device::turnOff();
        cout << name << " is now turned OFF.\n";
    }
};

class Fan : public Device {
public:
    Fan(string fanName) : Device(fanName) {}

    void turnOn() override {
        Device::turnOn();
        cout << name << " is now turned ON.\n";
    }

    void turnOff() override {
        Device::turnOff();
        cout << name << " is now turned OFF.\n";
    }
};

class SecurityCamera : public Device {
public:
    SecurityCamera(string cameraName) : Device(cameraName) {}

    void turnOn() override {
        Device::turnOn();
        cout << name << " is now turned ON and monitoring.\n";
    }

    void turnOff() override {
        Device::turnOff();
        cout << name << " is now turned OFF and not monitoring.\n";
    }
};

class HomeAutomationSystem {
private:
    vector<Device*> devices;

public:
    void addDevice(Device* device) {
        devices.push_back(device);
    }

    void interactWithDevices() {
        string command;
        while (true) {
            cout << "\nCurrent Device Status:\n";
            for (size_t i = 0; i < devices.size(); ++i) {
                cout << i + 1 << ". " << devices[i]->showStatus() << endl;
            }

            cout << "\nWould you like to change a device's status or exit? (enter 'change' or 'exit'): ";
            cin >> command;

            if (command == "exit") {
                cout << "Exiting Home Automation System. Goodbye!\n";
                break;
            } else if (command == "change") {
                cout << "Select a device by number (or 0 to cancel): ";
                int choice;
                cin >> choice;

                if (choice == 0) {
                    cout << "Cancelled.\n";
                    continue;
                }

                if (choice < 1 || choice > devices.size()) {
                    cout << "Invalid choice. Try again.\n";
                    continue;
                }

                Device* selectedDevice = devices[choice - 1];
                cout << "Do you want to turn ON the " << selectedDevice->showStatus() << "? (yes/no): ";
                string response;
                cin >> response;

                if (response == "yes") {
                    selectedDevice->turnOn();
                } else if (response == "no") {
                    selectedDevice->turnOff();
                } else {
                    cout << "Invalid response. Skipping...\n";
                }
            } else {
                cout << "Invalid command. Please enter 'change' or 'exit'.\n";
            }
        }
    }

    ~HomeAutomationSystem() {
        for (auto device : devices) {
            delete device;
        }
    }
};

int main() {
    HomeAutomationSystem home;

    home.addDevice(new Light("Living Room Light"));
    home.addDevice(new Fan("Living Room Fan"));
    home.addDevice(new Light("Bedroom Light"));
    home.addDevice(new Fan("Bedroom Fan"));
    home.addDevice(new Light("Bathroom Light"));
    home.addDevice(new Fan("Bathroom Fan"));
    home.addDevice(new Light("Kitchen Light"));
    home.addDevice(new Fan("Kitchen Fan"));
    home.addDevice(new SecurityCamera("Front Door Camera"));
    home.addDevice(new SecurityCamera("Backyard Camera"));

    home.interactWithDevices();

    return 0;
}
