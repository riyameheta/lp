% Dynamic predicates to store employee performance data
:- dynamic(employee_quality/2).

% Initial facts (employee, rating)
employee_quality('John', 8).
employee_quality('Alice', 7).
employee_quality('Bob', 9).

% Categorize employee quality of work
categorize_quality(Rating, Category) :-
    Rating >= 8,
    Category = 'Excellent'.
categorize_quality(Rating, Category) :-
    Rating >= 6,
    Rating < 8,
    Category = 'Good'.
categorize_quality(_, 'Average').

% Evaluate employee quality of work
evaluate_quality(Employee, Rating, Category) :-
    employee_quality(Employee, Rating),
    categorize_quality(Rating, Category), !.

evaluate_quality(_, _, 'Quality of work data not found for this employee.').

% Add employee quality of work data
add_quality(Employee, Rating) :-
    assertz(employee_quality(Employee, Rating)),
    write('Employee quality of work data added successfully.'), nl.

% Remove employee quality of work data
remove_quality(Employee) :-
    retractall(employee_quality(Employee, _)),
    write('Employee quality of work data removed successfully.'), nl.

% Menu
menu :-
    repeat,
    nl, write('---------- Employee Quality of Work Evaluation ----------'), nl,
    write('1. Evaluate Quality of Work'), nl,
    write('2. Add Quality of Work Data'), nl,
    write('3. Remove Quality of Work Data'), nl,
    write('4. Exit'), nl,
    write('-----------------------------------------------------------'), nl,
    write('Enter your choice (1-4): '), read(Choice),
    process_choice(Choice),
    Choice == 4, !.

% Process user choice
process_choice(1) :-
    nl, write('Enter employee name: '), read(Employee),
    evaluate_quality(Employee, Rating, Category),
    write('Quality of Work Rating: '), write(Rating), nl,
    write('Category: '), write(Category), nl.

process_choice(2) :-
    nl, write('Enter employee name: '), read(Employee),
    write('Enter quality of work rating: '), read(Rating),
    add_quality(Employee, Rating).

process_choice(3) :-
    nl, write('Enter employee name to remove quality of work data: '), read(Employee),
    remove_quality(Employee).

process_choice(4) :-
    nl, write('Exiting...'), nl.

% Entry point
:- initialization(menu).
