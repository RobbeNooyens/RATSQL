<p align="center">
     RATSQL
</p>

<p align="center">
     Machines and Complexity
</p>

<p align="center">
     2nd bachelor Computer Science - University of Antwerp
</p>

---

<p align="center">
     Made by Cédric Leclercq, Maarten Peirsman, Pablo Deputter and Robbe Nooyens
</p>

---

This year, next to machines and computability, we have another computer-related course that is completely new to us, 
namely the course "introduction to databases". During these classes so far we learned how to set up entity-relationship 
models, how to write queries in relational algebra and how to then translate them into a usable SQL query. Of course, 
with the naked eye and a little background knowledge, converting a simple expression to a SQL query is not that 
difficult. But what if the relational algebra expression becomes so complicated that the structure is hard to recognize? 
What if there was a program that could do this? 

That is what we too, were wondering. In combination with the parsers 
that we saw in the subject of machines and computability, this seemed to us the perfect combination to make a project 
around. So we wanted to create a program that takes as input an expression in relational algebra and gives as output a 
SQL query. We used an earley parser to do this. The basis of our project is the conversion of an expression to a query.
We then included an error detector that can see if a user wrote something wrong, and replace it is the user wants it. We
also used the shunting yard algorithm to make a relational algebra expression as optimal as possible.
For error detection we used the "Levenshtein distance". This method is 
used in computer science to calculate how many operations are needed to convert a string into another string b by adding, 
removing or replacing a character. Thus, it allows us to detect and replace simple spelling errors to avoid errors in 
our system. Like we said before, to implement nad make the query as optimal as possible, 
we are going to implement the Shunting-yard algorithm.  This algorithm allows us to treat expressions that are contained
in another expression first.

---


<p align="center">
     Notes
</p>

--- 

It needs to be noted that no enters are allowed in the direct input for parsing a relational algebra expression. When writing a
new enter, a new relational algebra expression is expected.

Some tests of the query tests fail, this is because the tests are written to the optimal output, and our generated
view creates some extra views (but is still fully correct).

---


<p align="center">
     Usage
</p>

--- 

Make sure that Qt 6 is installed (there is some support for Qt 5 for certain configurations, but limited). Secondly,
make sure to set the working directory to the project root.
