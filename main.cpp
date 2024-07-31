#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Task {
public:
    Task(const string& description = "") : description(description), completed(false) {}

    string getDescription() const {
        return this->description; // Using this pointer
    }

    bool isCompleted() const {
        return this->completed; // Using this pointer
    }

    void markAsComplete() {
        this->completed = true; // Using this pointer
    }

private:
    string description;
    bool completed;
};

class ToDoList {
public:
    void showMenu() const {
        cout << "----------------------------------------------------------------------\n";
        cout << "Please choose an option:\n";
        cout << "1. Add a task\n";
        cout << "2. Delete a task\n";
        cout << "3. View all tasks\n";
        cout << "4. Mark a task as complete\n";
        cout << "5. Exit\n";
    }

    void addTask() {
        cout << "Enter the task: ";
        string taskDescription;
        cin.ignore();
        getline(cin, taskDescription);
        this->tasks.emplace_back(taskDescription); // Using this pointer
        cout << "----------------------------------------------------------------------\n";
        cout << "Task added successfully.\n";
    }

    void deleteTask() {
        cout << "----------------------------------------------------------------------\n";
        if (this->tasks.empty()) { // Using this pointer
            cout << "No tasks available to delete.\n";
            return;
        }

        cout << "Enter the task number to delete: ";
        int taskNumber;
        cin >> taskNumber;

        if (taskNumber < 1 || taskNumber > this->tasks.size()) { // Using this pointer
            cout << "Invalid task number.\n";
        } else {
            this->tasks.erase(this->tasks.begin() + taskNumber - 1); // Using this pointer
            cout << "Task deleted successfully.\n";
        }
    }

    void viewTasks() const {
        cout << "----------------------------------------------------------------------\n";
        if (this->tasks.empty()) { // Using this pointer
            cout << "No tasks available.\n";
            return;
        }
        cout << "Tasks:\n";
        for (size_t i = 0; i < this->tasks.size(); ++i) { // Using this pointer
            cout << i + 1 << ". " << this->tasks[i].getDescription() << "\n"; // Using this pointer
            cout << "Status: " << (this->tasks[i].isCompleted() ? "Completed" : "Incomplete") << '\n'; // Using this pointer
        }
    }

    void markTaskAsComplete() {
        cout << "----------------------------------------------------------------------\n";
        if (this->tasks.empty()) { // Using this pointer
            cout << "No tasks available to mark as complete.\n";
            return;
        }

        this->viewTasks(); // Using this pointer
        cout << "Enter the task number to mark as complete: ";
        int taskNumber;
        cin >> taskNumber;

        if (taskNumber < 1 || taskNumber > this->tasks.size()) { // Using this pointer
            cout << "Invalid task number.\n";
        } else {
            this->tasks[taskNumber - 1].markAsComplete(); // Using this pointer
            cout << "----------------------------------------------------------------------\n";
            cout << "Task marked as complete successfully.\n";
        }
    }

private:
    vector<Task> tasks;
};

int main() {
    ToDoList toDoList;
    int choice;
    string input;
    cout << "----------------------------------------------------------------------\n";
    cout << "Welcome to your To-Do List Manager!\n";

    Task taskArray[3] = { Task("Task 1"), Task("Task 2"), Task("Task 3") };

    cout << "----------------------------------------------------------------------\n";
    cout << "Initial tasks from the array:\n";
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << ". " << taskArray[i].getDescription() << "\n";
        cout << "Status: " << (taskArray[i].isCompleted() ? "Completed" : "Incomplete") << '\n';
    }

    do {
        toDoList.showMenu();
        cout << "Enter your choice: ";
        cin >> input;

        stringstream ss(input);
        if (!(ss >> choice) || !ss.eof()) {
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                toDoList.addTask();
                break;
            case 2:
                toDoList.deleteTask();
                break;
            case 3:
                toDoList.viewTasks();
                break;
            case 4:
                toDoList.markTaskAsComplete();
                break;
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
