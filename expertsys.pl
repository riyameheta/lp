% Define rules for diagnosing various illnesses
diagnose_illness(Symptoms, cold) :-
    member(headache, Symptoms),
    member(runny_nose, Symptoms),
    member(sneezing, Symptoms),
    not(member(fever, Symptoms)).

diagnose_illness(Symptoms, flu) :-
    member(fever, Symptoms),
    member(body_aches, Symptoms),
    member(fatigue, Symptoms).

diagnose_illness(Symptoms, allergies) :-
    member(sneezing, Symptoms),
    member(itchy_eyes, Symptoms),
    member(runny_nose, Symptoms),
    not(member(fever, Symptoms)).

diagnose_illness(Symptoms, sinusitis) :-
    member(facial_pain, Symptoms),
    member(fever, Symptoms),
    member(nasal_congestion, Symptoms).

diagnose_illness(Symptoms, pneumonia) :-
    member(fever, Symptoms),
    member(cough, Symptoms),
    member(shortness_of_breath, Symptoms),
    member(chest_pain, Symptoms).

% Main predicate for diagnosing
diagnose(Symptoms, Diagnosis) :-
    diagnose_illness(Symptoms, Diagnosis),
    !. % Cut operator to stop searching after finding a diagnosis

% Example queries:
% diagnose([headache, runny_nose, sneezing], Diagnosis).
% diagnose([fever, cough, shortness_of_breath], Diagnosis).
% diagnose([sneezing, itchy_eyes, runny_nose], Diagnosis).