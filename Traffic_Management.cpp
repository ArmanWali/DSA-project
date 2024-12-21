#include <iostream>
#include <fstream> // For file handling
using namespace std;

class Vehicles{
    public:
    string id;
    string type;

    Vehicles(){
        id = "";
        type = "";
    }

    Vehicles(string id, string type){
        this->id = id;
        this->type = type;
    }

    void displayInfo(){
        cout<<" <-- ID: "<<id;
        // cout<<" Type: "<<type;
        // cout << "Number: ";
        // cout << "Number: ";
    }
    
};

class Node{
    public:
    Vehicles data;
    Node* next;

    Node(){
        data = Vehicles();
        next = nullptr;
    }

    Node(Vehicles data){
        this->data = data;
        next = nullptr;
    }
};

class ListQue{
    Node* front;
    Node* rear;

    public:
    ListQue(){
        front = nullptr;
        rear = nullptr;
    }

    void Enqueue(Vehicles data){
        Node* newNode = new Node(data);

        if (front == nullptr){
            front = rear = newNode;
        }
        else{
            rear->next = newNode;
            rear = newNode;
        }
    } 

    void Dequeue() {
        if (front == nullptr) {
            cout << "The queue is empty" << endl;
            return;
        }
        Node* temp = front;
        ofstream file("passed_vehicles.txt", ios::app);
        if (file.is_open()) {
            file << temp->data.id << endl; // Log the ID of the removed vehicle
            file.close();
        } else {
            cout << "Error: Unable to open the file for logging vehicle IDs." << endl;
        }

        cout << "Removing Vehicle ID: " << temp->data.id << " from the lane." << endl; // Added message
        front = front->next;
        delete temp;
        if (front == nullptr) { // Reset rear if queue is empty after dequeue
            rear = nullptr;
        }
    }

    void Display(){
        Node* temp = front;
        while (temp != nullptr){
            temp->data.displayInfo();
            temp = temp->next;
        }
        cout<<endl;
    }

    void Front(){
        if (front == nullptr){
            cout<<"The queue is empty"<<endl;
            return;
        }
        front->data.displayInfo();
    }

    void Rear(){
        if (rear == nullptr){
            cout<<"The queue is empty"<<endl;
            return;
        }
        rear->data.displayInfo();
    }

    void IsEmpty(){
        if (front == nullptr){
            cout<<"The queue is empty"<<endl;
        }
        else{
            cout<<"The queue is not empty"<<endl;
        }
    }

    void Clear() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;  // Reset rear to null after clearing
}

    ~ListQue(){
        Clear();
    }
    
};

class ArrayQue{
    public:
    int rear, front;
    static const int size = 5;
    Vehicles arr[size]; 

    ArrayQue(){
        rear = front = -1;
    }

    bool isFull(){
        return (rear == size - 1); 
    }

    bool isEmpty(){
        return front == -1;
    }

    void Enqueue(Vehicles value){
        if (isFull()){
            cout<<"The Lane is full, you can't add more vehicles!"<<endl;
            return;
        }
        if (isEmpty()){
            front = rear = 0;
            arr[rear] = value;
            return;
        }
        arr[++rear] = value; 
    }

    void Dequeue() {
    if (isEmpty()) {
        cout << "The Lane is already Empty!" << endl;
        return;
    }
    ofstream file("passed_vehicles.txt", ios::app);
        if (file.is_open()) {
            file << arr[front].id << endl;
            file.close();
        } else {
            cout << "Error: Unable to open the file for logging vehicle IDs." << endl;
        }

    cout << "Removing Vehicle ID: " << arr[front].id << " from the lane." << endl; // Added message
    if (front == rear) {
        front = rear = -1;
    } else {
        front++;
    }
}

    void Display(){
        for (int i = front; i <= rear; i++){
            arr[i].displayInfo();
        }
    }
};

class TrafficSignal{
    public:
    string state;
    int duration;

    TrafficSignal(){
        state = "Red";
        duration = 10;
    }

    void changeSignal(int elapsedTime) {
        while (elapsedTime > 0) {
            if (elapsedTime < duration) {
                duration -= elapsedTime;
                break;
            }
            elapsedTime -= duration;
            if (state == "Red") {
                state = "Green";
                duration = 15;
            } else if (state == "Green") {
                state = "Yellow";
                duration = 5;
            } else if (state == "Yellow") {
                state = "Red";
                duration = 10;
            }
        }
}


    void displaySignal() {
        cout << "Signal: " << state << " | Remaining Duration: " << duration << " seconds" << endl;
    }

    bool canPass(){
        return state == "Green";
    }
};

class Road {
public:
    ListQue TruckLane_list;
    ListQue CarLane_list;
    ListQue BikeLane_list;

    ArrayQue TruckLane_array;
    ArrayQue CarLane_array;
    ArrayQue BikeLane_array;

    TrafficSignal TruckSignal;
    TrafficSignal CarSignal;
    TrafficSignal BikeSignal;

    int inputMode; // 1 for Linked List, 2 for Array

    Road() {
        inputMode = 0;
    }

    void setInputMode() {
    cout << "1. Use Linked List." << endl;
    cout << "2. Use Array." << endl;
    cout << "Enter choice: ";
    cin >> inputMode;
    if (inputMode != 1 && inputMode != 2) {
        cout << "Invalid choice. Defaulting to Linked List." << endl;
        inputMode = 1;
    } else {
        cout << (inputMode == 1 ? "Using Linked List" : "Using Array") << " for lane management." << endl;
    }
}


    void AddVehiclesToLane(Vehicles vehicle) {

        if (vehicle.type != "Truck" && vehicle.type != "Car" && vehicle.type != "Bike") {
        cout << "Invalid vehicle type. Please enter Truck, Car, or Bike." << endl;
        return;
    }
        if (inputMode == 1) {
            if (vehicle.type == "Truck") {
                TruckLane_list.Enqueue(vehicle);
            } else if (vehicle.type == "Car") {
                CarLane_list.Enqueue(vehicle);
            } else if (vehicle.type == "Bike") {
                BikeLane_list.Enqueue(vehicle);
            } else {
                cout << "Unknown Vehicle type" << endl;
            }
        } else if (inputMode == 2) {
            if (vehicle.type == "Truck") {
                TruckLane_array.Enqueue(vehicle);
            } else if (vehicle.type == "Car") {
                CarLane_array.Enqueue(vehicle);
            } else if (vehicle.type == "Bike") {
                BikeLane_array.Enqueue(vehicle);
            } else {
                cout << "Unknown Vehicle type" << endl;
            }
        }
    }

    void DequeueVehiclesFromLanes(string LaneType) {
        if (inputMode == 1) {
            if (LaneType == "Truck") {
                if (TruckSignal.canPass()) {
                    TruckLane_list.Dequeue();
                } else {
                    cout << "Truck Lane Signal is not Green! Please wait" << endl;
                }
            } else if (LaneType == "Car") {
                if (CarSignal.canPass()) {
                    CarLane_list.Dequeue();
                } else {
                    cout << "Car Lane Signal is not Green! Please wait" << endl;
                }
            } else if (LaneType == "Bike") {
                if (BikeSignal.canPass()) {
                    BikeLane_list.Dequeue();
                } else {
                    cout << "Bike Lane Signal is not Green! Please wait" << endl;
                }
            }
        } else if (inputMode == 2) {
            if (LaneType == "Truck") {
                if (TruckSignal.canPass()) {
                    TruckLane_array.Dequeue();
                } else {
                    cout << "Truck Lane Signal is not Green! Please wait" << endl;
                }
            } else if (LaneType == "Car") {
                if (CarSignal.canPass()) {
                    CarLane_array.Dequeue();
                } else {
                    cout << "Car Lane Signal is not Green! Please wait" << endl;
                }
            } else if (LaneType == "Bike") {
                if (BikeSignal.canPass()) {
                    BikeLane_array.Dequeue();
                } else {
                    cout << "Bike Lane Signal is not Green! Please wait" << endl;
                }
            }
        }
    }

    void DisplayAllLanes() {
        if (inputMode == 1) {
            cout << "\nTrucks Lane (Linked List): ";
            TruckLane_list.Display();

            cout << "\nCars Lane (Linked List): ";
            CarLane_list.Display();

            cout << "\nBikes Lane (Linked List): ";
            BikeLane_list.Display();
        } else if (inputMode == 2) {
            cout << "\nTrucks Lane (Array): ";
            TruckLane_array.Display();

            cout << "\nCars Lane (Array): ";
            CarLane_array.Display();

            cout << "\nBikes Lane (Array): ";
            BikeLane_array.Display();
        }
    }

    void updateAllSignals(int elapsedTime) {
        TruckSignal.changeSignal(elapsedTime);
        CarSignal.changeSignal(elapsedTime);
        BikeSignal.changeSignal(elapsedTime);
    }

    void displayAllSignals() {
        cout << "\nTruck lane Signal: ";
        TruckSignal.displaySignal();

        cout << "Car Lane Signal: ";
        CarSignal.displaySignal();

        cout << "Bike lane Signal: ";
        BikeSignal.displaySignal();
    }
};

int main() {
    system("CLS");
    Road road;
    road.setInputMode();

    int choice;
    do {
        cout << "\nTraffic Management System Menu:" << endl;
        cout << "1. Add Vehicle to Lane" << endl;
        cout << "2. Remove Vehicle from Lane" << endl;
        cout << "3. Display All Lanes" << endl;
        cout << "4. Update Traffic Signals" << endl;
        cout << "5. Display Traffic Signals" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string id, type;
            cout << "Enter Vehicle ID: ";
            cin >> id;
            cout << "Enter Vehicle Type (Truck/Car/Bike): ";
            cin >> type;
            road.AddVehiclesToLane(Vehicles(id, type));
            break;
        }

        case 2: {
            string laneType;
            cout << "Enter Lane Type to Remove Vehicle (Truck/Car/Bike): ";
            cin >> laneType;
            road.DequeueVehiclesFromLanes(laneType);
            break;
        }

        case 3:
            road.DisplayAllLanes();
            break;

        case 4: { 
        int elapsedTime; 
        cout << "Enter elapsed time in seconds to update signals: "; 
        cin >> elapsedTime; 
        road.updateAllSignals(elapsedTime); 
        cout << "Signals updated!" << endl; 
        break; 
    }
        case 5:
            road.displayAllSignals();
            break;

        case 6:
            cout << "Exiting the system. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
