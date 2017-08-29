# ExpertSystem

Backward-chaining inference engine.

This two-man project is a simple inference engine. That means it is a program that makes deductions.

To achieve this, we have a number of facts, that for our program we will call by letters, like "A", "B", or "C", and which can be "TRUE" or "FALSE". By default, all our facts are "FALSE".

Then, we have a number of rules, that have a format like "A + B => C", and which defines results that are "TRUE".
These rules uses several operators: "+" means "AND", "|" means "OR", and some others.

Next, we have the initials facts, in the form of "=ABC", and finally, we have the query, in the form of "?A".

With these elements, we can create simple systems, that our program will solve. Here is a simple example:
```
A + B => C # this is a rule
=A # A is true by default.
?C # what is the value of C?
```

In this case, C is false, because A AND B implies C. However, only A is TRUE. 
Now see this modification:
```
A | B => C
=A
?C
```
Now, C is true, because the rule is A OR B, and A is TRUE, so C is TRUE.


What is the point of all this nonsense you ask?
Well this is the basis of what is called an Expert System.

Imagine this same resolver with a huge database of thousands of rules and facts, about medicine for example. Now we have a patient with symptoms.

We enter the symptoms into the expert system, and we have an illness name.

Well this program is the basis of that. For more on expert system, see [this page](https://en.wikipedia.org/wiki/Expert_system).
