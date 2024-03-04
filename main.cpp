//
//  main.cpp
//  Project 2
// CS300 SNHU
// Created by Jacob Batrano on 2/25/24.


//  After considering the requirements and constraints of my course management system project, I have decided to switch from using a hash table to a vector data structure. The primary reason for this transition is the simplicity and straightforwardness that vectors offer. Given that my dataset is relatively small and the performance gains from a hash table's typical O(1) time complexity are not substantial, a vector proves to be an effective solution. Vectors maintain the order of elements, which is beneficial for the frequent operation of displaying courses sequentially, such as in a course catalog. Moreover, the need for complex collision handling inherent in hash tables is eliminated with vectors, simplifying the implementation. Though vectors may have a higher time complexity for certain operations, their ease of use, direct access to elements, and excellent support in C++ standard libraries make them a practical choice for this project. This approach aligns with my goal to create a manageable, maintainable codebase while providing an adequate level of performance for the expected usage patterns.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class Course {
public:
    std::string courseNumber; // Unique identifier for the course
    std::string title; // Title of the course
    std::vector<std::string> prerequisites; // List of prerequisites for the course

    // Constructor
    Course(std::string cn, std::string t, std::vector<std::string> prereqs)
        : courseNumber(std::move(cn)), title(std::move(t)), prerequisites(std::move(prereqs)) {}

    // Display function for a single course.
    void display() const {
        std::cout << courseNumber << ", " << title << std::endl;
    }

};


// Function to read course data from a file and load into a vector
void loadCoursesFromFile(const std::string& fileName, std::vector<Course>& courses) {
    std::ifstream file(fileName); // Open the file stream
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return; // Exit if the file cannot be opened
    }
    std::string line;
    // Read each line from the file and construct Course objects
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string courseNumber, title;
        std::vector<std::string> prerequisites;
        getline(iss, courseNumber, ',');
        getline(iss, title, ',');
        std::string prereq;
        while (getline(iss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }
        courses.emplace_back(courseNumber, title, prerequisites);
    }
    // Sort the courses by course number in ascending order
    std::sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
    });
    file.close(); // Close the file after loading data
}

// Function to print all courses
void printAllCourses(const std::vector<Course>& courses) {
    for (const auto& course : courses) {
        course.display(); // Calls the  display function
    }
}

// Function to find and print a specific course
void printSpecificCourse(const std::vector<Course>& courses) {
    std::string courseNumber;
    std::cout << "Enter course number: ";
    std::cin >> courseNumber;

    auto it = std::find_if(courses.begin(), courses.end(), [&courseNumber](const Course& course) {
        return course.courseNumber == courseNumber;
    });

    if (it != courses.end()) {
        // Use the displayWithPrerequisites function if the course is found
        std::cout << it->courseNumber << ", " << it->title << std::endl;
        if (!it->prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (const auto& prereq : it->prerequisites) {
                std::cout << prereq << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Prerequisites: None" << std::endl; // Handle no prerequisites
        }
    } else {
        std::cout << "Course not found." << std::endl;
    }
}
// Function to display the menu of the application
void displayScholarlyMenu() {
    std::cout << "\n========================================\n";
    std::cout << " ABCU Academic Course Management Interface\n";
    std::cout << "========================================\n";
    std::cout << "1) Load Data Structure\n";
    std::cout << "2) Print Course List\n";
    std::cout << "3) Print Course\n";
    std::cout << "4) Exit\n";
    std::cout << "Select an option: ";
}

// Main function to run the Academic Course Management Interface
int main() {
    std::vector<Course> courses; // Holds the list of courses
    std::string fileName; // Filename to load courses from
    bool dataLoaded = false; // Flag to check if data is loaded
   
    // Display the menu and process user input
    displayScholarlyMenu();
    int choice = 0;
    while (choice != 4) {
        std::cin >> choice;

        // Check for input failure, clear it, and ignore the rest of the input
              if (std::cin.fail()) {
                  std::cin.clear();
                  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                  std::cout << "Invalid input. Please enter a number." << std::endl;
                  continue;
              }
        // Handle the user's menu choice
               switch (choice) {
                   case 1:
                       // Load the data structure with courses from the file
                       std::cout << "Enter the file name with course data: ";
                       std::cin >> fileName;
                       loadCoursesFromFile(fileName, courses);
                       dataLoaded = true; // Set flag to true indicating data is loaded
                       std::cout << "Courses loaded successfully." << std::endl;
                       break;
                   case 2:
                       // Print the course list if data is loaded
                       if (!dataLoaded) {
                           std::cout << "Please load the data structure first." << std::endl;
                       } else {
                           printAllCourses(courses);
                       }
                       break;
                   case 3:
                       // Print information for a specific course if data is loaded
                       if (!dataLoaded) {
                           std::cout << "Please load the data structure first." << std::endl;
                       } else {
                           printSpecificCourse(courses);
                       }
                       break;
                   case 4:
                       // Exit the program
                       std::cout << "Exiting the Academic Course Management Interface." << std::endl;
                       break;
                   default:
                       // Handle invalid menu options
                       std::cout << "Invalid option. Please try again." << std::endl;
                       break;
               }
               // Re-display the menu unless the user chooses to exit
               if (choice != 4) {
                   displayScholarlyMenu();
               }
           }

           return 0; // End of program
       }
