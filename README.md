# Weighted Student GPA Calculation Program

The task of this assignment is to create a program that:

1. Allows a user to enter as many course letter grades (A, B, C, D, F) with course hour values and semester and year indicators.
2. Calculates the GPA based on those letter grades and hours for each semester that has data entered for it, in addition to an overall GPA.
3. Display the GPA and credit hours earned for each of the semesters with data.
4. Display the overall GPA correctly calculated from all credit hours. 

How to Calculate GPA
1. For each course, multiply credits by grade points
2. Add those results to get total quality points
3. Divide total quality points by total number of credits for courses where you earned a letter grade

(We are using a standard 4.0 scale for this calculation)

For example:  
```shell
admin@computer$  gpa_calculation
----> To quit entering grades, enter a blank line.
Enter a letter grade and hours for a course with its year and semester: A 3 FALL 2025
Enter a letter grade and hours for a course with its year and semester: B 2 FALL 2025
Enter a letter grade and hours for a course with its year and semester: B 3 FALL 2025
Enter a letter grade and hours for a course with its year and semester: A 3 FALL 2025
Enter a letter grade and hours for a course with its year and semester: B 3 SPRING 2025
Enter a letter grade and hours for a course with its year and semester: B 3 SPRING 2025
Enter a letter grade and hours for a course with its year and semester:
-------------------------------------
Unofficial Transcript
FALL   2025 (11 hours) 3.545
SPRING 2025 (6 hours) 3.000

--
Total credit hours: 17
Overall GPA: 3.353
-------------------------------------
```

## Detailed Program Specifications:

- Your program should be written in the C programming language
- Instructions to the user should be clear
- Allows the user to enter as many letter grades and hour combinations for as many class for as many years and for only the SPRING, FALL, or SUMMER semesters.
  - Account for uppercase and lowercase letters (grades and semester names)
- Properly calculate GPA average for each semester and an overall gpa
- Anytime a GPA is displayed, it should be displayed to *exactly* three decimal places
- Code should be well-formatted and properly commented
- Your code comments should explain what your code is doing
- The code must be void of any syntax errors and should run.

## Hints:

- You will need to use at least one looping structure
- Run your code often to catch bugs early. **Iterative development** is a must!
- Dynamic memory might make this easier to implement.

## Think you are finished? Ask yourself these questions:

- [ ] Does my code run?
- [ ] Does my program satisfy the requirements listed above?
- [ ] If I run the program with an A 3 SPRING 2025, B 3 SPRING 2025, and C 3 SPRING 2025, is the GPA for SPRING 2025 3.0? Is an A with 3 credit hours and a B with 2 credit hours GPA average calculated to 3.600?
- [ ] Did I account for abnormal user input? (or rather, will my program break if someone enters "}[v'34243inm sPrInG 1111" as a grade and course hours?) (What years should be valid?)
- [ ] Does my program work when the users immediately quits entering grades without entering any?
