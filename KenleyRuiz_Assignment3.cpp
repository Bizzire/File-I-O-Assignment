/*
Assignment 3 - File I/O, random number generator
-------------------------------------
COP3014-001 : Programmming II
KenleyRuiz_Assignment3.cpp
Created by Kenley Ruiz on 2/20/24.
-------------------------------------
Last modified:
2/23/24 - 10:35pm
*/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/*
    I realized that maybe the student shouldn't have the functionality 
    of grading the quiz. To fix this issue I could create a teacher class 
    and give it a grading function, but I will not in the scope of 
    this project due to time constraints
*/

/**
 * @brief Student class that has functionality and attributes for each student object
*/
class Student
{
private:
    // Student functions and attributes
    int generate_total_quizzes(int);
    void grade_quiz();
    int quizzes[10]; // Holds all quiz grades
    int total_quizzes;
    string student_name;

public:
    // Constructors
    /**
    * @brief constructor creates Student object with name parameter
    *
    * @param name the students name (string)
    */
    Student(string name);

    // Getters
    /**
     * @brief functions to return students name, 
     *        get total amount of quizzes and get quiz grades
     * 
     * @return get_student_name - returns students name
     *         get_total_quizzes - returns the total of quizzes that the student took
     *         get_quiz_grades - returns the quiz grade based on index number
     * 
     * @param index_number index number to access quizzes array, should be used in a loop
    */
    string get_student_name();
    int get_total_quizzes();
    int get_quiz_grades(int index_number);
};

// Function declarations - explanations can be found on function definitions
int generate_between_0_and_10();
int generate_between_1_and_20();
void write_student_data(Student, ofstream&);
void generate_input_file();
void generate_output_file(int, int);
string calculate_average(int, int);
int quiz_total_per_student(ifstream&, string);
int extract_number_from_string(string str);

/**
* @brief MAIN FUNCTION TO RUN THE PROGRAM
*/
int main()
{
    int const MAX_QUIZZES = 10;
    int const MAX_STUDENTS = 10;
    srand(time(0));
    generate_input_file();
    generate_output_file(MAX_STUDENTS, MAX_QUIZZES);

    return 0;
}

// Constructor
Student::Student(string name)
{
    student_name = name;
    generate_total_quizzes(10);
    grade_quiz();
}

/**
 * @brief Generates number between 0 and 10
 * 
 * @return returns a random number between 0 and 10
 * 
 * @param MAX_QUIZZES the max amount of quizzes per student = 10
*/
int generate_between_0_and_10(int MAX_QUIZZES)
{
    int a_number;
    a_number = rand() % MAX_QUIZZES + 1;

    return a_number;
}

/**
 * @brief Generates number between 1 and 20
 * 
 * @return returns a random number between 1 and 20
*/
int generate_between_1_and_20()
{
    int a_number;
    a_number = (rand() % 20) + 1;

    return a_number;
}

/**
 * @brief Generates input file of students name along with grades per quiz
*/
void generate_input_file()
{
    string const INPUT_FILE = "input_file.txt";

    // Creating 10 student objects for input file
    Student randal_bob("Randal, Bob");
    Student delony_danny("Delony, Danny");
    Student cooly_carly("Cooly, Carly");
    Student genius_gina("Genius, Gina");
    Student william_bobby("William, Bobby");
    Student squarepants_spongebob("Squarepants, Spongebob");
    Student star_patrick("Star, Patrick");
    Student turner_timmy("Turner, Timmy");
    Student neutron_jimmy("Neutron, Jimmy");
    Student phantom_danny("Phantom, Danny");

    ofstream input_file(INPUT_FILE);

    if(input_file.fail())
    {
        cout << "Failed to open input_file.txt, now exiting....";
        exit(1);
    }

    write_student_data(randal_bob, input_file);
    write_student_data(delony_danny, input_file);
    write_student_data(cooly_carly, input_file);
    write_student_data(genius_gina, input_file);
    write_student_data(william_bobby, input_file);
    write_student_data(squarepants_spongebob, input_file);
    write_student_data(star_patrick, input_file);
    write_student_data(turner_timmy, input_file);
    write_student_data(neutron_jimmy, input_file);
    write_student_data(phantom_danny, input_file);

    cout << "Input file created successfully.." << endl;

    input_file.close();
}

/**
 * @brief Writes the students quizzes and scores into the input file
 * 
 * @param student_object an object of class student
 * @param input_file the input file that has all students names and quiz scores
*/
void write_student_data(Student student_object, ofstream& input_file)
{
    input_file << student_object.get_student_name() << " ";

    for(int i = 0; i < student_object.get_total_quizzes(); i++)
    {
        input_file << student_object.get_quiz_grades(i) << " ";
    }

    input_file << endl;
}

/**
 * @brief Generates output file to include average of student quiz grades
 * 
 * @param MAX_STUDENTS the max amount of students in the class = 10
 * @param MAX_QUIZZES the max amount of quizzes per student = 10
*/
void generate_output_file(int MAX_STUDENTS, int MAX_QUIZZES)
{
    string const INPUT_FILE = "input_file.txt";
    string const OUTPUT_FILE = "output_file.txt";
    string grades;
    string lines_from_input[MAX_STUDENTS];
    string student_averages[MAX_STUDENTS];
    int student_totals[MAX_STUDENTS];

    ifstream input_file(INPUT_FILE);
    ofstream output_file(OUTPUT_FILE);

    if(input_file.fail())
    {
        cout << "Failed to open input_file.txt, now exiting....";
        exit(1);
    }
    
    if(output_file.fail())
    {
        cout << "Failed to open input_file.txt, now exiting....";
        exit(1);
    }

    for(int i = 0; i < MAX_STUDENTS; i++)
    {
        getline(input_file,grades);

        lines_from_input[i] = grades;
        student_totals[i] = quiz_total_per_student(input_file, grades);
        student_averages[i] = calculate_average(student_totals[i], MAX_QUIZZES);
    }

    output_file << "\"This file displays the student grades along with the average score for each student.\"" << endl << endl;

    for(int i = 0; i < MAX_STUDENTS; i++)
    {
        output_file << lines_from_input[i] << ": " << student_averages[i] << endl;
    }

    cout << "Output file created successfully.." << endl;

    input_file.close();
    output_file.close();
}

/**
* @brief Calculates average of students quiz grades, 
*        passing student object to calculate average for that specific student
*
* @return returns the average from students quiz scores
*
* @param student_total the sum of all student quiz scores
* @param MAX_QUIZZES the max amount of quizzes per student = 10
*/
string calculate_average(int student_total, int MAX_QUIZZES)
{
    double average = 0;
    int position = 0;
    string converted_average;

    average = student_total / (double)MAX_QUIZZES;
    converted_average = to_string(average);

    for(int i = 0; i < converted_average.length(); i++)
    {
        if(converted_average[i] == '.')
        {
            position = i;
        }
    }

    position = position + 2;
    converted_average.erase(position, 4);

    return converted_average;
}

/**
* @brief Function returns the sum of all quiz scores per student 
*
* @return returns the sum of all quiz scores of that student
*
* @param input_file the input file that has all students names and quiz scores
* @param grades string containing line of input_file
*/
int quiz_total_per_student(ifstream& input_file, string grades)
{
    int total = 0;
    
    total = extract_number_from_string(grades);

    return total;
}

/**
* @brief Function extracts numbers from the input_file line and then sums all integers 
*
*        Code used and manipulated from:
*        https://www.geeksforgeeks.org/extract-integers-string-c/
*        Loops through string stream to find integers, for each integer found
*        I added them together to return the total for that current line
*
* @return returns the sum of all quiz scores of that student 
*
* @param str string containing line of input_file
*/
int extract_number_from_string(string str)
{
    stringstream ss;
    ss << str;
    string temp;
    int found;
    int total = 0;
    while (!ss.eof()) {
         ss >> temp;
         if (stringstream(temp) >> found)
            total += found;
        temp = "";
     }
     return total;
}

/**
* @brief Getter function that returns students name
*
* @return returns students name
*/
string Student::get_student_name()
{
    return student_name;
}

/**
* @brief Getter function that gets total amount of quizzes
*
* @return returns total amount of quizzes that the student took
*/
int Student::get_total_quizzes()
{
    return total_quizzes;
}

/**
* @brief Getter function that gets students quiz grades, index number is passed to verify quiz score
*
* @return returns students quiz grade thats stored in students quizzes array
*
* @param index_number the index number that is needed to extract quiz grade from students quizzes array
*/
int Student::get_quiz_grades(int index_number)
{
    int quiz_grade;
    quiz_grade = quizzes[index_number];
    
    return quiz_grade;
}

/**
* @brief Private function to generate random number of quizzes
*
* @return returns total amount of quizzes that the student took
*
* @param MAX_QUIZZES the max amount of quizzes per student = 10
*/
int Student::generate_total_quizzes(int MAX_QUIZZES)
{
    total_quizzes = generate_between_0_and_10(MAX_QUIZZES);
    
    return total_quizzes;
}

/**
* @brief Private function to randomly grade students quizzes
*/
void Student::grade_quiz()
{
    for(int i = 0; i < total_quizzes; i++)
    {
        quizzes[i] = generate_between_1_and_20();
    }
}