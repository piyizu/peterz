/*
	Designed and Coded by Peter Zu
	School of Informatics, Xiamen University
	Student Number: 22920202202873
	Created on 19 July, 2021
*/
#define _CRT_SECURE_NO_WARNINGS

//LAWS of Coding
/*
	1. Clear the standard input buffer right after each input if the fuction does not do this task.
	2. After calling fgets(), remove the newline character. 
	3. Linked list operation needs "p = p->next"
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <windows.h>

#define NUM_STRING_MAX 64
#define NAME_STRING_MAX 256
#define INTRO_STRING_MAX 512
#define STU_COURSES_MAX 64

//Definitions of data structures:
struct course {
	char no[NUM_STRING_MAX], name[NAME_STRING_MAX], teacher[NAME_STRING_MAX], intro[INTRO_STRING_MAX];
	double credits;
	unsigned long long int stu_max, stu_taken;
	struct course* next;
};

struct student {
	//One student can take at most STU_COURSES_MAX courses.
	char no[NUM_STRING_MAX];
	int num_course_taken; //how many courses the student takes
	char cousre_taken[STU_COURSES_MAX][NUM_STRING_MAX]; //the course number of courses taken
	double total_credits;
	struct student* next;
};

//Declarations of fuctions:
void open(struct course** course_head, struct student** stu_head);
void stu_management(struct course** course_head, struct student** stu_head);
void course_management(struct course** course_head, struct student** stu_head);
void course_ava(struct course* course_head, struct student* stu_head);
void course_chosen(struct course* course_head, struct student* stu_head);
void choose(struct course** course_head, struct student** stu_head);
void throw_away(struct course** course_head, struct student** stu_head);
void save(struct course* p, struct student* q);
void delete_data_in_RAM(struct course** course_head, struct student** stu_head);
void print(struct course* p1, struct student* p2);
void course_detail(struct course* course_head);


//Definitions of fuctions:
void open(struct course** course_head, struct student** stu_head) {
	FILE* course_data, * stu_data;
	if (course_data = fopen(".\\cs.bin", "rb")) {
		struct course* pre = NULL, * p = NULL;

		//This is a fantastic method of dealing with those files:
		unsigned long long int count;
		fread(&count, sizeof(unsigned long long int), 1, course_data);

		printf("We are loading %llu items from cs.bin...\n", count);

		while (count--) {
			p = (struct course*)malloc(sizeof(struct course));
			if (p == NULL) exit(EXIT_FAILURE);
			fread(p, sizeof(struct course), 1, course_data);
			p->next = NULL;

			if (*course_head == NULL) *course_head = p;
			else if (pre) pre->next = p;
			pre = p;
		}

		printf("Loaded!\n");

	}
	else {
		course_data = fopen(".\\cs.bin", "wb");
		if (course_data == NULL) exit(EXIT_FAILURE);
		printf("No cs.bin was found. But we create an empty new one!\n");
	}

	if (stu_data = fopen(".\\st.bin", "rb")) {

		unsigned long long int count;
		fread(&count, sizeof(unsigned long long int), 1, stu_data);

		printf("We are loading %llu items from st.bin...\n", count);

		struct student* pre = NULL, * p = NULL;
		while (count--) {
			p = (struct student*)malloc(sizeof(struct student));
			if (p == NULL) exit(EXIT_FAILURE);
			fread(p, sizeof(struct student), 1, stu_data);
			p->next = NULL;

			if (*stu_head == NULL) *stu_head = p;
			else if (pre) pre->next = p;
			pre = p;
		}

		printf("Loaded!\n");

	}
	else {
		stu_data = fopen(".\\st.bin", "wb");
		if (stu_data == NULL) exit(EXIT_FAILURE);
		printf("No st.bin was found. But we create an empty new one!\n");
	}

	fclose(course_data);
	fclose(stu_data);

}

void stu_management(struct course **course_head, struct student** stu_head) {
	printf(" Add a student? Delete a student? (a/d): ");
	char ch;
	scanf_s("%c", &ch, 1);
	while (getchar() != '\n') continue;
	switch (ch) {
	case 'a':
	case 'A': {
		struct student* temp = (struct student*)malloc(sizeof(struct student));
		if (temp == NULL) exit(EXIT_FAILURE);

		printf(" Student Number (%d WORDS AT MOST):", NUM_STRING_MAX - 1);
		fgets(temp->no, NUM_STRING_MAX, stdin);
		(temp->no)[strlen(temp->no) - 1] = 0;

		struct student* p = *stu_head;
		while (p) {
			if (strcmp(p->no, temp->no) == 0) {
				printf("***Student already exists! Operation failed!***\n");
				free(temp);
				return;
			}
			if (p->next) p = p->next;
			else break;
		}

		temp->num_course_taken = 0;
		temp->total_credits = 0.0;
		temp->next = NULL;

		if (*stu_head == NULL) *stu_head = temp;
		else p->next = temp;

		printf("***Student added successfully!***\n");

		break;
		}
	case 'd':
	case 'D': {
		char stu_to_del[NUM_STRING_MAX];
		printf(" Student Number (%d WORDS AT MOST):", NUM_STRING_MAX - 1);
		fgets(stu_to_del, NUM_STRING_MAX, stdin);
		stu_to_del[strlen(stu_to_del) - 1] = 0;

		bool found = false;
		char course_stu_taken[STU_COURSES_MAX][NUM_STRING_MAX];
		int num_course_stu_taken;

		struct student* p = *stu_head;
		if (strcmp((*stu_head)->no, stu_to_del) == 0) {
			found = true;
			p = (*stu_head)->next;
			memcpy(course_stu_taken, (*stu_head)->cousre_taken, sizeof(course_stu_taken));
			num_course_stu_taken = (*stu_head)->num_course_taken;
			free(*stu_head);
			(*stu_head) = p;
		}
		else {
			while (p->next) {
				if (strcmp(p->next->no, stu_to_del) == 0) {
					found = true;
					struct student* temp = p->next->next;
					memcpy(course_stu_taken, p->next->cousre_taken, sizeof(course_stu_taken));
					num_course_stu_taken = (*stu_head)->num_course_taken;
					free(p->next);
					p->next = temp;
					break;
				}
				if (p->next) p = p->next;
				else break;
			}
		}
		
		if (found) {
			for (int i = 0; i < num_course_stu_taken; ++i) {
				struct course* q = (*course_head);
				while (q) {
					if (strcmp(q->no, course_stu_taken[i]) == 0) {
						--(q->stu_taken);
						break;
					}
					q = q->next;
				}
			}
			printf("***Student deleted successfully!***\n");
		}
		else {
			printf("***Student does not exist! Operation failed!***\n");
			return;
		}
	}
	default: break;
	}
}

void course_management(struct course** course_head, struct student **stu_head) {
	printf(" Add a course? Delete a course? (a/d): ");
	char ch;
	scanf_s("%c", &ch, 1);
	while (getchar() != '\n') continue;
	switch (ch) {
	case 'a':
	case 'A': {
		struct course* temp = (struct course*)malloc(sizeof(struct course));
		if (temp == NULL) exit(EXIT_FAILURE);

		printf(" Course Number (%d WORDS AT MOST):", NUM_STRING_MAX - 1);
		fgets(temp->no, NUM_STRING_MAX, stdin);
		(temp->no)[strlen(temp->no) - 1] = 0;

		struct course* p = *course_head;
		while (p) {
			if (strcmp(p->no, temp->no) == 0) {
				printf("***Course already exists! Operation failed!***\n");
				free(temp);
				return;
			}
			if (p->next) p = p->next;
			else break;
		}

		printf(" Course Name (%d WORDS AT MOST):", NAME_STRING_MAX - 1);
		fgets(temp->name, NAME_STRING_MAX, stdin);
		temp->name[strlen(temp->name) - 1] = 0;
		printf(" Teacher(s) (%d WORDS AT MOST):", NAME_STRING_MAX - 1);
		fgets(temp->teacher, NAME_STRING_MAX, stdin);
		temp->teacher[strlen(temp->teacher) - 1] = 0;
		printf(" Credit(s) of the course:");
		scanf_s("%lf", &temp->credits);
		while (getchar() != '\n') continue;
		printf(" Maximal number of students:");
		scanf_s("%llu", &temp->stu_max);
		while (getchar() != '\n') continue;
		temp->stu_taken = 0;
		printf(" Brief introduction of the Course (%d WORDS AT MOST):\n", INTRO_STRING_MAX - 1);
		fgets(temp->intro, INTRO_STRING_MAX, stdin);
		temp->intro[strlen(temp->intro) - 1] = 0;
		temp->next = NULL;

		if (*course_head == NULL) *course_head = temp;
		else p->next = temp;

		printf("***Course added successfully!***\n");
		break;
	}
	case 'd':
	case 'D': {
		printf(" Course Number (%d WORDS AT MOST):", NUM_STRING_MAX - 1);
		char num_course_to_del[NUM_STRING_MAX];
		double credits_course_to_del;

		fgets(num_course_to_del, NUM_STRING_MAX, stdin);
		num_course_to_del[strlen(num_course_to_del) - 1] = 0;

		struct course * p = *course_head;

		bool found = false;

		if (strcmp((*course_head)->no, num_course_to_del) == 0) {
			found = true;
			p = (*course_head)->next;
			credits_course_to_del = (*course_head)->credits;
			free(*course_head);
			*course_head = p;
		}
		else {
			while (p->next) {
				if (strcmp(p->next->no, num_course_to_del) == 0) {
					found = true;
					struct course* temp = p->next->next;
					credits_course_to_del = p->next->credits;
					free(p->next);
					p->next = temp;
					break;
				}
				p = p->next;
			}
		}

		if (found) {
			struct student* q = *stu_head;
			while (q) {
				bool found_in_stu = false;
				for (int i = 0; i < q->num_course_taken; ++i) {
					if ( (!found_in_stu) && ( strcmp( (q->cousre_taken)[i], num_course_to_del) == 0 ) ) {
						found_in_stu = true;
						continue;
					}
					if (found_in_stu) {
						strcpy( (q->cousre_taken)[i - 1], (q->cousre_taken)[i]);
					}
				}
				if (found_in_stu) {
					--(q->num_course_taken);
					q->total_credits -= credits_course_to_del;
				}
				q = q->next;
			}
			printf("***Course deleted successfully!***\n");
		}
		else {
			printf("***Course does not exist! Operation failed!***\n");
			return;
		}
	}
	default: break;
	}
}

void course_ava(struct course* course_head, struct student* stu_head) {
	printf(" Student Number (%d WORDS AT MOST): ", NUM_STRING_MAX - 1);
	char stu_no_viewing[NUM_STRING_MAX];
	fgets(stu_no_viewing, NUM_STRING_MAX, stdin);
	stu_no_viewing[strlen(stu_no_viewing) - 1] = 0;
	
	struct student* p = stu_head;
	bool found = false;
	while (p) {
		if (strcmp(p->no, stu_no_viewing) == 0) {
			found = true;
			break;
		}
		p = p->next;
	}
	if (found) {
		if (p->num_course_taken == STU_COURSES_MAX) {
			printf("***This student has reached the maxium of courses!***\n");
			return;
		}
		else {
			printf("|     Course Number     |                Course Name                |Stus|Capacity|\n");
			struct course* q = course_head;
			while (q) {
				if (q->stu_max == q->stu_taken) {
					q = q->next;
					continue;
				}
				bool chosen_by_this_student = false;
				for (int i = 0; i < p->num_course_taken; ++i) {
					if (strcmp(p->cousre_taken[i], q->no) == 0) {
						chosen_by_this_student = true;
						break;
					}
				}
				if (!chosen_by_this_student) {
					printf(" %-24s %-43s %-4llu  %-7llu\n", q->no, q->name, q->stu_taken, q->stu_max);
				}
				q = q->next;
			}
			printf("---END OF THE LIST---\n");
		}
	}
	else {
		printf("***Student does not exist! Operation failed!***\n");
		return;
	}
}

void course_chosen(struct course* course_head, struct student* stu_head) {
	printf(" Student Number (%d WORDS AT MOST): ", NUM_STRING_MAX - 1);
	char stu_no_viewing[NUM_STRING_MAX];
	fgets(stu_no_viewing, NUM_STRING_MAX, stdin);
	stu_no_viewing[strlen(stu_no_viewing) - 1] = 0;

	struct student* p = stu_head;
	bool found = false;
	while (p) {
		if (strcmp(p->no, stu_no_viewing) == 0) {
			found = true;
			break;
		}
		p = p->next;
	}

	if (found) {
		printf("|      Course Number       |                Course Name               |  Credits  |\n");
		for (int i = 0; i < p->num_course_taken; ++i) {
			struct course* q = course_head;
			while (q) {
				if (strcmp(q->no, p->cousre_taken[i]) == 0)
					break;
				q = q->next;
			}
			if(q != NULL) printf("  %-26s %-42s %-10.2lf\n", q->no, q->name, q->credits);
		}
		printf("\n Total Credits:        %-10.2lf\n", p->total_credits);
		printf("---END OF THE LIST---\n");
	}
	else {
		printf("***Student does not exist! Operation failed!***\n");
		return;
	}
}

void choose(struct course **course_head, struct student **stu_head) {
	printf(" Student Number (%d WORDS AT MOST): ", NUM_STRING_MAX - 1);
	char stu_no_viewing[NUM_STRING_MAX];
	fgets(stu_no_viewing, NUM_STRING_MAX, stdin);
	stu_no_viewing[strlen(stu_no_viewing) - 1] = 0;

	struct student* p = *stu_head;
	bool found = false;
	while (p) {
		if (strcmp(p->no, stu_no_viewing) == 0) {
			found = true;
			break;
		}
		p = p->next;
	}

	if (found) {
		if (p->num_course_taken == STU_COURSES_MAX) {
			printf("***This student has reached the maxium of courses!***\n");
			return;
		}
		else {
			printf(" Course Number (%d WORDS AT MOST):", NUM_STRING_MAX - 1);
			char num_course_to_add[NUM_STRING_MAX];
			fgets(num_course_to_add, NUM_STRING_MAX, stdin);
			num_course_to_add[strlen(num_course_to_add) - 1] = 0;

			struct course* q = *course_head;
			bool course_found = false;

			while (q) {
				if (strcmp(q->no, num_course_to_add) == 0) {
					course_found = true;
					break;
				}
				q = q->next;
			}

			if (course_found) {
				if (q->stu_max == q->stu_taken) {
					printf("***The course has reached its capacity!***\n");
					return;
				}
				else { 
					//one student can not take the same course twice
					for (int i = 0; i < p->num_course_taken; ++i) {
						if (strcmp((p->cousre_taken)[i], num_course_to_add) == 0) {
							printf("***Course chosen! Operation failed!***\n");
							return;
						}
					}

					++(q->stu_taken);

					strcpy(p->cousre_taken[p->num_course_taken], q->no);
					++(p->num_course_taken);
					p->total_credits += q->credits;

					printf("***Congratulations! Operation succeeds!***\n");
					return;
				}
			}
			else {
				printf("***Course does not exist! Operation failed!***\n");
				return;
			}
		}
	}
	else {
		printf("***Student does not exist! Operation failed!***\n");
		return;
	}
}

void throw_away(struct course** course_head, struct student** stu_head) {
	printf(" Student Number (%d WORDS AT MOST): ", NUM_STRING_MAX - 1);
	char stu_no_viewing[NUM_STRING_MAX];
	fgets(stu_no_viewing, NUM_STRING_MAX, stdin);
	stu_no_viewing[strlen(stu_no_viewing) - 1] = 0;

	struct student* p = *stu_head;
	bool found = false;
	while (p) {
		if (strcmp(p->no, stu_no_viewing) == 0) {
			found = true;
			break;
		}
		p = p->next;
	}

	if (found) {
		if (p->num_course_taken == 0) {
			printf("***This student takes no course! Operation failed!***\n");
			return;
		}
		else {
			printf(" Course Number (%d WORDS AT MOST):", NUM_STRING_MAX - 1);
			char num_course_to_throw[NUM_STRING_MAX];
			fgets(num_course_to_throw, NUM_STRING_MAX, stdin);
			num_course_to_throw[strlen(num_course_to_throw) - 1] = 0;

			struct course* q = *course_head;
			bool course_found = false;

			while (q) {
				if (strcmp(q->no, num_course_to_throw) == 0) {
					course_found = true;
					break;
				}
				q = q->next;
			}

			if (!course_found) {
				printf("***Course does not exist! Operation failed!***\n");
				return;
			}

			bool course_found_in_stu = false;

			int i; //var i can be used later
			for (i = 0; i < p->num_course_taken; ++i) {
				if (strcmp(p->cousre_taken[i], num_course_to_throw) == 0) {
					course_found_in_stu = true;
					break;
				}
			}

			if (!course_found_in_stu) {
				printf("***This student has not yes taken the course! Operation failed!***\n");
				return;
			}

			--(q->stu_taken);

			for (; i < p->num_course_taken - 1; ++i) {
				strcpy(p->cousre_taken[i], p->cousre_taken[i + 1]);
			}
			--(p->num_course_taken);
			p->total_credits -= q->credits;
			printf("***Congratulations! Operation succeeds!***\n");
			return;
		}
	}
	else {
		printf("***Student does not exist! Operation failed!***\n");
		return;
	}
}

void save(struct course* p, struct student* q) {

	FILE *course_data = fopen(".\\cs.bin", "wb");
	if (course_data == NULL) exit(EXIT_FAILURE);
	FILE *stu_data = fopen(".\\st.bin", "wb");
	if (stu_data == NULL) exit(EXIT_FAILURE);

	unsigned long long int count_course = 0, count_stu = 0;
	fwrite(&count_course, sizeof(unsigned long long int), 1, course_data);
	fwrite(&count_stu, sizeof(unsigned long long int), 1, stu_data);
	
	while (p) {
		fwrite(p, sizeof(struct course), 1, course_data);
		++count_course;
		p = p->next;
	}
	while (q) {
		fwrite(q, sizeof(struct student), 1, stu_data);
		++count_stu;
		q = q->next;
	}

	rewind(course_data);
	rewind(stu_data);
	fwrite(&count_course, sizeof(unsigned long long int), 1, course_data);
	fwrite(&count_stu, sizeof(unsigned long long int), 1, stu_data);

	fclose(course_data);
	fclose(stu_data);
	printf("***Data Saved!***\n");
}

void delete_data_in_RAM(struct course** course_head, struct student** stu_head) {
	while (*course_head) {
		struct course* temp = (*course_head)->next;
		free((*course_head));
		(*course_head) = temp;
	}
	while (*stu_head) {
		struct student* temp = (*stu_head)->next;
		free((*stu_head));
		(*stu_head) = temp;
	}
}

void print(struct course* p1, struct student* p2) {
	printf("| Course No. |           Course Name           |     Teacher(s)     |Credits|Stus|Capacity|\n");
	while (p1) {
		printf(" %-13s %-33s %-20s %-5.2lf %4llu %7llu\n", p1->no, p1->name, p1->teacher, p1->credits,
			p1->stu_taken, p1->stu_max);
		p1 = p1->next;
	}
	printf("\n|           Student No.           | Num of Courses | Total Credits |\n");
	while (p2) {
		printf("  %-35s %-16d %-15.2lf\n", p2->no, p2->num_course_taken, p2->total_credits);
		p2 = p2->next;
	}
	printf("---PRINT TO THE SCREEN COMPLETED---\n");
}

void course_detail(struct course * course_head) {
	char course_no[NUM_STRING_MAX];
	printf(" Course Number (%d WORDS AT MOST):", NUM_STRING_MAX - 1);
	fgets(course_no, NUM_STRING_MAX, stdin);
	course_no[strlen(course_no) - 1] = 0;

	struct course* p = course_head;
	while (p) {
		if (strcmp(p->no, course_no) == 0)
			break;
		p = p->next;
	}

	if (p == NULL) {
		printf("***Course does not exist! Operation failed!***\n");
		return;
	}
	else {
		printf(" Course Name: %s\n Teacher(s):  %s\n Credits:     %.2lf\n", p->name, p->teacher, p->credits);
		printf(" Number of Students Taking this Course: %llu\n", p->stu_taken);
		printf(" Course Capacity:                       %llu\n", p->stu_max);
		printf(" ==================INTRODUCTION=================\n   %s\n", p->intro);
		printf("\n---ALL IS ABOVE---\n");
	}
}

int main() {
	struct course* course_head = NULL;
	struct student* stu_head = NULL;
	char ch = 0;

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		   "  Piyi ZU, School of Informatics, Xiamen University\n"
		   "  Student Number: 22920202202873\n"
		   "  My Teacher: Qingyang Hong\n"
		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Loading files from the disc...\n");
	open(&course_head, &stu_head);
	printf("Done! And welcome to our system!\n");
	printf("Press any key to continue...");

	if ( (ch = getchar() ) != '\n') //to pause before showing the menu
		while (getchar() != '\n') continue;
	system("cls");

	
	while (ch != 'q' && ( printf("\n>>>Course Selection System<<<\n\n"
								">Course and Student Management Part<\n"
								"    1.Add or delete a course.\n"
								"    2.Add or delete a student.\n\n"
								">Viewing Part<\n"
								"    3.View available courses for a student.\n"
								"    4.View chosen courses and total credits of a student.\n"
								"    c.View detailed information of a course\n\n"
								">Operation Part<\n"
								"    5.Choose a new course for a student.\n"
								"    6.Throw a chosen course away for a student.\n\n"
								">Data Operation Part<\n"
								"    p.Print the courses and the students.\n"
								"    s.Save data to the disc.\n\n"
								" q.Quit.\n>>") > 0 )
		) {
		scanf_s("%c", &ch, 1);
		while (getchar() != '\n') continue;

		system("cls");

		switch (ch) {
		case '1':
			printf(">>Course Management Subprogram<<\n");
			course_management(&course_head, &stu_head);
			break;
		case '2':
			printf(">>Student Management Subprogram<<\n");
			stu_management(&course_head, &stu_head);
			break;
		case '3':
			printf(">>Viewing Available Courses<<\n");
			course_ava(course_head, stu_head);
			break;
		case '4':
			printf(">>Viewing Chosen Courses<<\n");
			course_chosen(course_head, stu_head);
			break;
		case '5':
			printf(">>To Choose A New Course<<\n");
			choose(&course_head, &stu_head);
			break;
		case '6':
			printf(">>To Throw Away A Chosen Course<<\n");
			throw_away(&course_head, &stu_head);
			break;
		case 'p':
		case 'P':
			printf(">>Printing<<\n");
			print(course_head, stu_head);
			break;
		case 'c':
		case 'C':
			printf(">>Viewing Detailed Information of A Course<<\n");
			course_detail(course_head);
			break;
		case 's':
		case 'S':
			save(course_head, stu_head);
			break;
		default: 
			break;
		}

		//the following will run after invalid selections or finishing of a subprogram
		if (ch != 'q') {
			printf("Type 'q' to directly exit or 'ENTER' to go back to the menu...");
			if ((ch = getchar()) != '\n')
				while (getchar() != '\n') continue;
			system("cls");
		}
	}

	save(course_head, stu_head);
	printf("***Data Saved to the Disc Automatically and Successfully!***\n");

	delete_data_in_RAM(&course_head, &stu_head);
	if (course_head == NULL && stu_head == NULL) printf("\n***Successfully deleted contents in memmory!***\n");

	printf("Press any key to continue...");
	ch = getchar();

	return 0;
}