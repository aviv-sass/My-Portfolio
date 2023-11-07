# Technion Study Path Recommender - "המומלצת המומלצת"
<p align="center">
<img src="Hamumlezet - Logo.png" width="300">
</p>

## Introduction
Technion – Israel Institute of Technology is a public research university in Haifa, Israel, specializing in engineering and precise sciences. With 18 faculties and academic units, it is a leader in technological research in Israel.
This project aims to assist students in planning their semester and degree schedule. While the Technion provides a recommended schedule (המערכת המומלצת), students often face difficulties in customizing it according to their preferences and needs. The challenge of balancing different subjects, meeting prerequisites, and avoiding academic irregularities calls for a more personalized solution.



🚀 Exciting Project Alert: Hamumlezet Hamumlezet!

🌟 Project Overview:
While studying at the Technion, my team <tag>, <tag>, and I identified a prevalent issue among students. Many believe there’s a more optimal semester syllabus than the one recommended by the faculty. This belief leads students to construct their own semester syllabus, a process that is often challenging and results in imbalances in workload and difficulty levels in courses and exams. These challenges can lead to academic struggles and stress for students.

🛠 Our Solution:
To address this, 


## Problem & Solution
### Problem
Many tudents believe there’s a more optimal semester syllabus than the one recommended by the faculty (המערכת המומלצת). This belief leads students to construct their own semester syllabus, a process that is often challenging and results in imbalances in workload and difficulty levels in courses and exams. These challenges can lead to academic struggles and stress for students.
### Solution
An AI-based system that recommends the best personalized path for students until the end of their degree (המומלצת המומלצת).
The system aims for the student's optimal success in studies and successful graduation.
## System Structure
### Main Components
1. **Course:** Object representing a course, including name, credits, prerequisites, schedule, etc.
2. **State:** Represents the student's academic status in relation to the study program.
3. **Student:** The student's input profile.
### Key Parts
1. **Data Infrastructure:** Collects and organizes the necessary data for the entire program run.
2. **Course Graph:** Represents the courses and their relations in a Directed Acyclic Graph (DAG).
3. **Options Graph:** Constructs all possible legal paths to complete the degree.
4. **Search:** Uses the A* algorithm to find the optimal path, with various heuristics based on preferences.
The system is implemented in Python, utilizing the networkx library for handling graphs and other libraries.

### Feel free to get a closer look at the system design and functionality!

<img src="system design.jpg" width="30000">

