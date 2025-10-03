// main.c
#include "locale.h"
#include "tree.h"
#include <stdio.h>
// #define RUN_MAIN_PROGRAM

#ifdef RUN_MAIN_PROGRAM

// main.c
int main() {
  setlocale(LC_ALL, "Rus");

  printf("=== ��������� ���������� ������ ����� ===\n\n");

  // ������� �������� ���� input.txt
  printf("1. ������� �������� ���� input.txt...\n");
  FILE *input = fopen("input.txt", "w");
  if (input == NULL) {
    printf("������ �������� ����� input.txt!\n");
    return 1;
  }

  // ���������� �������� ������ �������� ������� �� �������
  fprintf(input, "7\n");
  fprintf(input, "WINNT\\SYSTEM32\\CONFIG\n");
  fprintf(input, "GAMES\n");
  fprintf(input, "WINNT\\DRIVERS\n");
  fprintf(input, "HOME\n");
  fprintf(input, "WIN\\SOFT\n");
  fprintf(input, "GAMES\\DRIVERS\n");
  fprintf(input, "WINNT\\SYSTEM32\\CERTSRV\\CERTCO~1\\X86\n");

  fclose(input);
  printf("   ���� input.txt ������ �������!\n\n");

  // ������ ���� �� �����
  printf("2. ������ ���� �� �����...\n");
  PathList *paths = read_paths_from_file("input.txt");
  if (paths == NULL) {
    printf("������ ������ ����� input.txt\n");
    return 1;
  }

  // ������� �������� ����
  printf("3. ������� ������ �����...\n");
  TreeNode *root = create_node("");
  if (root == NULL) {
    printf("������ ��������� ������ ��� ��������� ����!\n");
    free_path_list(paths);
    return 1;
  }

  // ��������� ��� ���� � ������
  PathList *current_path = paths;
  while (current_path != NULL) {
    add_path_to_tree(root, current_path->path);
    current_path = current_path->next;
  }

  // ��������� ������
  printf("4. ��������� ������...\n");
  sort_tree(root);

  // ������� ��������� � ���� output.txt
  printf("5. ��������� ��������� � output.txt...\n");
  FILE *output = fopen("output.txt", "w");
  if (output == NULL) {
    printf("������ �������� ����� output.txt!\n");
    free_tree(root);
    free_path_list(paths);
    return 1;
  }

  print_tree_to_file(root->child, 0, output);

  fclose(output);
  printf("   ���� output.txt �������� �������!\n\n");

  // ������� ���������� output.txt �� �����
  printf("6. ���������� output.txt:\n");
  printf("========================\n");

  FILE *output_read = fopen("output.txt", "r");
  if (output_read != NULL) {
    char line[256];
    while (fgets(line, sizeof(line), output_read)) {
      printf("%s", line);
    }
    fclose(output_read);
  }
  printf("========================\n\n");

  // ����������� ������
  printf("7. ����������� ������...\n");
  free_tree(root);
  free_path_list(paths);
  printf("   ������ ����������� �������!\n\n");

  printf("=== ��������� ��������� ===\n");
  printf("������� Enter ��� ������...");
  getchar();

  return 0;
}
#endif