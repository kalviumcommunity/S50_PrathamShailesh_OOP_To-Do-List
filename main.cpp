#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Task {
public:
    // Parameterized constructor (also acts as a default constructor)
    Task(const string& description = "") : description(description), completed(false) {
        taskCount++;
    }

    // Copy constructor
    Task(const Task& other) {
        this->description = other.description;
        this->completed = other.completed;
        taskCount++;
        if (this->completed) {
            completedTaskCount++;
        }
    }

    // Destructor
    ~Task() {
        if (completed) {
            completedTaskCount--;
        }
        taskCount--;
        cout << "Task '" << description << "' is being deleted.\n";
    }

    // Accessor (getter) method for task description
    string getDescription() const {
        return this->description; 
    }

    // Accessor (getter) method for task completion status
    bool isCompleted() const {
        return this->completed; 
    }

    // Mutator (setter) method to mark task as complete
    void markAsComplete() {
        if (!this->completed) { 
            this->completed = true;
            completedTaskCount++;
        }
    }

    // Static accessor to get total task count
    static int getTaskCount() {
        return taskCount;
    }

    // Static accessor to get completed task count
    static int getCompletedTaskCount() {
        return completedTaskCount;
    }

    // Static mutator to decrement task count
    static void decrementTaskCount() {
        if (taskCount > 0) {
            --taskCount;
        }
    }

    // Static mutator to decrement completed task count
    static void decrementCompletedTaskCount() {
        if (completedTaskCount > 0) {
            --completedTaskCount;
        }
    }

private:
    // Private member variables to protect internal data
    string description;  // The task description is hidden from direct access
    bool completed;      // The completion status is private

    // Static member variables to track task counts, also private
    static int taskCount;  
    static int completedTaskCount;  
};

// Initialize static members outside the class
int Task::taskCount = 0;
int Task::completedTaskCount = 0;

class ToDoList {
public:
    // Method to show the main menu
    void showMenu() const {
        cout << "----------------------------------------------------------------------\n";
        cout << "Please choose an option:\n";
        cout << "1. Add a task\n";
        cout << "2. Delete a task\n";
        cout << "3. View all tasks\n";
        cout << "4. Mark a task as complete\n";
        cout << "5. Exit\n";
    }

    // Mutator method to add a task
    void addTask() {
        cout << "Enter the task: ";
        string taskDescription;
        cin.ignore();
        getline(cin, taskDescription);
        Task* newTask = new Task(taskDescription); // Using Task constructor (mutator) to set description
        this->tasks.push_back(newTask);
        cout << "----------------------------------------------------------------------\n";
        cout << "Task added successfully. Total tasks: " << Task::getTaskCount() << "\n"; // Accessing total task count using accessor
    }

    // Mutator method to delete a task
    void deleteTask() {
        cout << "----------------------------------------------------------------------\n";
        if (this->tasks.empty()) { 
            cout << "No tasks available to delete.\n";
            return;
        }

        cout << "Enter the task number to delete: ";
        int taskNumber;
        cin >> taskNumber;

        if (taskNumber < 1 || taskNumber > this->tasks.size()) { 
            cout << "Invalid task number.\n";
        } else {
            // Check if the task is completed using the accessor
            if (this->tasks[taskNumber - 1]->isCompleted()) {  // Accessor to check if task is completed
                Task::decrementCompletedTaskCount(); // Mutator to decrement completed task count
            }
            delete this->tasks[taskNumber - 1]; // Deleting task
            this->tasks.erase(this->tasks.begin() + taskNumber - 1); 
            Task::decrementTaskCount();  // Mutator to decrement total task count
            cout << "Task deleted successfully.\n";
            cout << "Total tasks remaining: " << Task::getTaskCount() << "\n"; // Accessor for task count
        }
    }

    // Accessor method to view all tasks
    void viewTasks() const {
        cout << "----------------------------------------------------------------------\n";
        if (this->tasks.empty()) { 
            cout << "No tasks available.\n";
            return;
        }
        cout << "Tasks:\n";
        for (size_t i = 0; i < this->tasks.size(); ++i) { 
            cout << i + 1 << ". " << this->tasks[i]->getDescription() << "\n";  // Accessor to get task description
            cout << "Status: " << (this->tasks[i]->isCompleted() ? "Completed" : "Incomplete") << '\n';  // Accessor for task status
        }
        cout << "----------------------------------------------------------------------\n";
        cout << "Total completed tasks: " << Task::getCompletedTaskCount() << "\n";  // Accessor for completed task count
    }

    // Mutator method to mark a task as complete
    void markTaskAsComplete() {
        cout << "----------------------------------------------------------------------\n";
        if (this->tasks.empty()) { 
            cout << "No tasks available to mark as complete.\n";
            return;
        }

        this->viewTasks(); 
        cout << "Enter the task number to mark as complete: ";
        int taskNumber;
        cin >> taskNumber;

        if (taskNumber < 1 || taskNumber > this->tasks.size()) { 
            cout << "Invalid task number.\n";
        } else {
            this->tasks[taskNumber - 1]->markAsComplete();  // Mutator to mark the task as complete
            cout << "----------------------------------------------------------------------\n";
            cout << "Task marked as complete successfully.\n";
            cout << "Total completed tasks: " << Task::getCompletedTaskCount() << "\n";  // Accessor for completed task count
        }
    }

    ~ToDoList() {
        for (Task* task : tasks) {
            delete task;
        }
    }

private:
    // Private member variable to store the tasks (hidden from outside access)
    vector<Task*> tasks;  
};

int main() {
    ToDoList toDoList;
    int choice;
    string input;
    cout << "----------------------------------------------------------------------\n";
    cout << "Welcome to your To-Do List Manager!\n";

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
