// tests.c
#include "tree.h"
#include <assert.h>
#include <string.h>
#include <locale.h>

#define RUN_MAIN_PROGRAM

#ifdef RUN_MAIN_PROGRAM

// ��������������� ������� ��� ��������� ��������
int compare_trees(TreeNode* expected, TreeNode* actual) {
    if (expected == NULL && actual == NULL) return 1;
    if (expected == NULL || actual == NULL) return 0;
    if (strcmp(expected->name, actual->name) != 0) return 0;

    return compare_trees(expected->child, actual->child) &&
        compare_trees(expected->next, actual->next);
}

// ���� 1: �������� ���� � �������� ������
void TestCreateNode_ValidName_no1() {
    printf("Test 1: �������� ���� � �������� ������... ");
    TreeNode* node = create_node("test");
    assert(node != NULL);
    assert(strcmp(node->name, "test") == 0);
    assert(node->next == NULL);
    assert(node->child == NULL);
    free(node);
    printf("PASSED\n");
}

// ���� 2: �������� ���� � NULL ������
void TestCreateNode_NullName_no2() {
    printf("Test 2: �������� ���� � NULL ������... ");
    TreeNode* node = create_node(NULL);
    assert(node == NULL);
    printf("PASSED\n");
}

// ���� 3: �������� ���� � ������ ������
void TestCreateNode_EmptyName_no3() {
    printf("Test 3: �������� ���� � ������ ������... ");
    TreeNode* node = create_node("");
    assert(node != NULL);
    assert(strcmp(node->name, "") == 0);
    free(node);
    printf("PASSED\n");
}

// ���� 4: ����� ������������� �������
void TestFindChild_ExistingChild_no4() {
    printf("Test 4: ����� ������������� �������... ");
    TreeNode* parent = create_node("parent");
    TreeNode* child1 = create_node("child1");
    TreeNode* child2 = create_node("child2");

    add_child(parent, child1);
    add_child(parent, child2);

    TreeNode* found = find_child(parent, "child1");
    assert(found != NULL);
    assert(strcmp(found->name, "child1") == 0);

    free_tree(parent);
    printf("PASSED\n");
}

// ���� 5: ����� ��������������� �������
void TestFindChild_NonExistingChild_no5() {
    printf("Test 5: ����� ��������������� �������... ");
    TreeNode* parent = create_node("parent");
    TreeNode* child = create_node("child");

    add_child(parent, child);

    TreeNode* found = find_child(parent, "nonexistent");
    assert(found == NULL);

    free_tree(parent);
    printf("PASSED\n");
}

// ���� 6: ���������� ���� � ������
void TestAddPathToTree_SingleLevel_no6() {
    printf("Test 6: ���������� �������������� ����... ");
    TreeNode* root = create_node("");

    add_path_to_tree(root, "folder1");

    assert(root->child != NULL);
    assert(strcmp(root->child->name, "folder1") == 0);
    assert(root->child->child == NULL);

    free_tree(root);
    printf("PASSED\n");
}

// ���� 7: ���������� ��������������� ����
void TestAddPathToTree_MultiLevel_no7() {
    printf("Test 7: ���������� ��������������� ����... ");
    TreeNode* root = create_node("");

    add_path_to_tree(root, "folder1\\subfold\\file1");

    assert(root->child != NULL);
    assert(strcmp(root->child->name, "folder1") == 0);
    assert(root->child->child != NULL);
    assert(strcmp(root->child->child->name, "subfold") == 0);
    assert(root->child->child->child != NULL);
    assert(strcmp(root->child->child->child->name, "file1") == 0);

    free_tree(root);
    printf("PASSED\n");
}

// ���� 8: ���������� �����
void TestSortChildren_Unsorted_no8() {
    printf("Test 8: ���������� �����... ");
    TreeNode* parent = create_node("parent");
    TreeNode* child3 = create_node("ccc");
    TreeNode* child1 = create_node("aaa");
    TreeNode* child2 = create_node("bbb");

    add_child(parent, child3);
    add_child(parent, child1);
    add_child(parent, child2);

    sort_children(parent);

    assert(parent->child != NULL);
    assert(strcmp(parent->child->name, "aaa") == 0);
    assert(parent->child->next != NULL);
    assert(strcmp(parent->child->next->name, "bbb") == 0);
    assert(parent->child->next->next != NULL);
    assert(strcmp(parent->child->next->next->name, "ccc") == 0);

    free_tree(parent);
    printf("PASSED\n");
}

// ���� 9: ���������� � ������ �����
void TestAddToPathList_ValidPath_no9() {
    printf("Test 9: ���������� � ������ �����... ");
    PathList* head = NULL;

    head = add_to_path_list(head, "path1");
    head = add_to_path_list(head, "path2");

    assert(head != NULL);
    assert(strcmp(head->path, "path2") == 0);
    assert(head->next != NULL);
    assert(strcmp(head->next->path, "path1") == 0);

    free_path_list(head);
    printf("PASSED\n");
}

// ���� 10: ��������� NULL ����������
void TestNullParameters_Safety_no10() {
    printf("Test 10: ��������� NULL ����������... ");

    // ��� ��� ������ �� ������ �������� ����
    add_child(NULL, NULL);
    find_child(NULL, NULL);
    add_path_to_tree(NULL, NULL);
    sort_children(NULL);
    sort_tree(NULL);
    print_tree_to_file(NULL, 0, NULL);

    printf("PASSED\n");
}

// ���� 11: ������������ ������
void TestMemoryFree_NoLeaks_no11() {
    printf("Test 11: ������������ ������... ");

    TreeNode* root = create_node("");
    add_path_to_tree(root, "a\\b\\c");
    add_path_to_tree(root, "x\\y\\z");

    free_tree(root); 

    PathList* paths = NULL;
    paths = add_to_path_list(paths, "path1");
    paths = add_to_path_list(paths, "path2");

    free_path_list(paths); 

    printf("PASSED\n");
}

// ���� 12: ��������� ������ - ��� �� 8 �������� (�������� �������)
void TestMaxLengthName_Exactly8Chars_no12() {
    printf("Test 12: ��������� ������ - ��� �� 8 ��������... ");
    TreeNode* node = create_node("12345678");  
    assert(node != NULL);
    assert(strcmp(node->name, "12345678")==0);
    assert(strlen(node->name) == 8);
    free(node);
    printf("PASSED\n");
}

// ���� 13: ����������� ������� � ������
void TestSpecialCharacters_AllowedSymbols_no13() {
    printf("Test 13: ����������� ������� � ������... ");
    TreeNode* node = create_node("#$%&()-@"); 
    assert(node != NULL);
    assert(strcmp(node->name, "#$%&()-@")==0);
    free(node);
    printf("PASSED\n");
}
// ���� 14: ��������� ������������� �����
void TestDuplicateFolders_NoDuplicates_no14() {
    printf("Test 14: ��������� ������������� �����... ");
    TreeNode* root = create_node("");

    add_path_to_tree(root, "common\\folder1");
    add_path_to_tree(root, "common\\folder1");  // ��������

    // ������ ���� ������ ���� ����� folder1
    assert(root->child != NULL);
    assert(strcmp(root->child->name, "common")==0);
    assert(root->child->child != NULL);
    assert(strcmp(root->child->child->name, "folder1")==0);
    // �� ������ ���� ���������
    assert(root->child->child->next == NULL);

    free_tree(root);
    printf("PASSED\n");
}
int main() {
    setlocale(LC_ALL, "Rus");
    printf("=== ������ ����-������ ===\n\n");

    TestCreateNode_ValidName_no1();
    TestCreateNode_NullName_no2();
    TestCreateNode_EmptyName_no3();
    TestFindChild_ExistingChild_no4();
    TestFindChild_NonExistingChild_no5();
    TestAddPathToTree_SingleLevel_no6();
    TestAddPathToTree_MultiLevel_no7();
    TestSortChildren_Unsorted_no8();
    TestAddToPathList_ValidPath_no9();
    TestNullParameters_Safety_no10();
    TestMemoryFree_NoLeaks_no11();
    TestMaxLengthName_Exactly8Chars_no12();
    TestSpecialCharacters_AllowedSymbols_no13();
    TestDuplicateFolders_NoDuplicates_no14();

    printf("\n=== ��� ����� �������� �������! ===\n");
    return 0;
}
#endif