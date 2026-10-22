
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[50];
    char department[50];
    struct Student *left;
    struct Student *right;
} Student;

long long comparisons = 0;

Student *createStudent(int id, const char name[],
                       const char department[]) {
    Student *node = (Student *)malloc(sizeof(Student));

    if (node == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    node->id = id;
    snprintf(node->name, sizeof(node->name), "%s", name);
    snprintf(node->department, sizeof(node->department),
             "%s", department);

    node->left = NULL;
    node->right = NULL;

    return node;
}

Student *insert(Student *root, int id, const char name[],
                const char department[]) {
    if (root == NULL) {
        printf("Student inserted successfully.\n");
        return createStudent(id, name, department);
    }

    comparisons++;

    if (id < root->id) {
        root->left = insert(root->left, id, name, department);
    } else if (id > root->id) {
        root->right = insert(root->right, id, name, department);
    } else {
        printf("Duplicate enrolment ID not allowed!\n");
    }

    return root;
}

Student *search(Student *root, int id) {
    while (root != NULL) {
        comparisons++;

        if (id == root->id) {
            return root;
        } else if (id < root->id) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return NULL;
}

Student *findMinimum(Student *root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }

    return root;
}

Student *deleteStudent(Student *root, int id) {
    Student *temp;

    if (root == NULL) {
        return NULL;
    }

    comparisons++;

    if (id < root->id) {
        root->left = deleteStudent(root->left, id);
    } else if (id > root->id) {
        root->right = deleteStudent(root->right, id);
    } else {
        /* Case 1 and 2: no left child or one right child */
        if (root->left == NULL) {
            temp = root->right;
            free(root);
            return temp;
        }

        /* Case 1 and 2: no right child or one left child */
        if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }

        /* Case 3: two children */
        temp = findMinimum(root->right);

        root->id = temp->id;
        strcpy(root->name, temp->name);
        strcpy(root->department, temp->department);

        root->right = deleteStudent(root->right, temp->id);
    }

    return root;
}

/* Inorder: ascending enrolment ID */
void inorder(Student *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d | %s | %s\n",
               root->id, root->name, root->department);
        inorder(root->right);
    }
}

/* Preorder traversal */
void preorder(Student *root) {
    if (root != NULL) {
        printf("%d | %s | %s\n",
               root->id, root->name, root->department);
        preorder(root->left);
        preorder(root->right);
    }
}

/* Postorder traversal */
void postorder(Student *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d | %s | %s\n",
               root->id, root->name, root->department);
    }
}

/* Display one student's details */
void displayStudent(Student *student) {
    if (student != NULL) {
        printf("\nStudent Found!\n");
        printf("Enrolment ID: %d\n", student->id);
        printf("Name: %s\n", student->name);
        printf("Department: %s\n", student->department);
    }
}

/* Count nodes in the BST */
int countStudents(Student *root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + countStudents(root->left)
             + countStudents(root->right);
}

/* Insert ten sample records */
Student *insertSamples(Student *root) {
    int ids[] = {50, 30, 70, 20, 40, 60, 80, 10, 35, 65};

    const char *names[] = {
        "Aman", "Priya", "Rahul", "Neha", "Rohan",
        "Simran", "Karan", "Anjali", "Vikas", "Pooja"
    };

    const char *departments[] = {
        "CSE", "IT", "ECE", "CSE", "IT",
        "ECE", "CSE", "IT", "ECE", "CSE"
    };

    int i;

    for (i = 0; i < 10; i++) {
        root = insert(root, ids[i], names[i], departments[i]);
    }

    return root;
}

/* Free allocated memory */
void freeTree(Student *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void) {
    Student *root = NULL;
    Student *found;
    int choice, id;
    char name[50], department[50];

    do {
        printf("\n====================================\n");
        printf("   STUDENT RECORD SEARCH SYSTEM\n");
        printf("====================================\n");
        printf("1. Insert Student\n");
        printf("2. Search Student\n");
        printf("3. Delete Student\n");
        printf("4. Inorder Traversal (Sorted)\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Insert 10 Sample Records\n");
        printf("8. Count Students\n");
        printf("9. Reset Comparison Counter\n");
        printf("10. Display Comparison Count\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            freeTree(root);
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Enter enrolment ID: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid input!\n");
                    freeTree(root);
                    return 1;
                }

                printf("Enter student name: ");
                scanf(" %49[^\n]", name);

                printf("Enter department: ");
                scanf(" %49[^\n]", department);

                root = insert(root, id, name, department);
                break;

            case 2:
                printf("Enter enrolment ID to search: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid input!\n");
                    freeTree(root);
                    return 1;
                }

                comparisons = 0;
                found = search(root, id);

                if (found != NULL) {
                    displayStudent(found);
                } else {
                    printf("Student not found!\n");
                }

                printf("Comparisons in search: %lld\n", comparisons);
                break;

            case 3:
                printf("Enter enrolment ID to delete: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid input!\n");
                    freeTree(root);
                    return 1;
                }

                comparisons = 0;
                found = search(root, id);

                if (found != NULL) {
                    comparisons = 0;
                    root = deleteStudent(root, id);
                    printf("Student deleted successfully.\n");
                    printf("Comparisons during deletion: %lld\n",
                           comparisons);
                } else {
                    printf("Student not found!\n");
                }
                break;

            case 4:
                printf("\nStudents in Ascending ID Order:\n");
                inorder(root);
                break;

            case 5:
                printf("\nPreorder Traversal:\n");
                preorder(root);
                break;

            case 6:
                printf("\nPostorder Traversal:\n");
                postorder(root);
                break;

            case 7:
                root = insertSamples(root);
                printf("Sample records processed.\n");
                printf("Total students: %d\n", countStudents(root));
                break;

            case 8:
                printf("Total student records: %d\n",
                       countStudents(root));
                break;

            case 9:
                comparisons = 0;
                printf("Comparison counter reset.\n");
                break;

            case 10:
                printf("Comparison count: %lld\n", comparisons);
                break;

            case 11:
                printf("Exiting Student Record Search System.\n");
                break;

            default:
                printf("Invalid choice! Select 1 to 11.\n");
        }

    } while (choice != 11);

    freeTree(root);
    return 0;
}

