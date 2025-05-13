#include "gtest/gtest.h"
#include "../s21_conteiner/Stack/s21_stack.h"
// #include "../s21_conteiner/Queue/s21_queue.h"
// #include "../s21_conteiner/List/s21_list.h"
// #include "../s21_conteiner/Vector/s21_vector.h"
// #include "../s21_conteiner/Map/s21_map.h"
// #include "../s21_conteiner/Set/s21_set.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // Флаги для выбора файлов с тестами
    bool run_all_tests = true;
    bool run_stack_tests = true;
    bool run_queue_tests = false;
    bool run_list_tests = false;
    bool run_vector_tests = false;
    bool run_map_tests = false;
    bool run_set_tests = false;

    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--no-all") == 0) {
            run_all_tests = false;
        } else if (strcmp(argv[i], "--no-stack") == 0) {
            run_stack_tests = false;
        } else if (strcmp(argv[i], "--no-queue") == 0) {
            run_queue_tests = false;
        } else if (strcmp(argv[i], "--no-list") == 0) {
            run_list_tests = false;
        } else if (strcmp(argv[i], "--no-vector") == 0) {
            run_vector_tests = false;
        } else if (strcmp(argv[i], "--no-map") == 0) {
            run_map_tests = false;
        } else if (strcmp(argv[i], "--no-set") == 0) {
            run_set_tests = false;
        }
    }

    // Запуск тестов в соответствии с флагами
    int result = 0;
    if (run_all_tests) {
        RUN_ALL_TESTS();
    } else {
        if (run_stack_tests) {
            ::testing::GTEST_FLAG(filter) = "StackTest.*";
            RUN_ALL_TESTS();
        }
        if (run_queue_tests) {
            ::testing::GTEST_FLAG(filter) = "QueueTest.*";
            RUN_ALL_TESTS();
        }
        if (run_list_tests) {
            ::testing::GTEST_FLAG(filter) = "ListTest.*";
            RUN_ALL_TESTS();
        }
        if (run_vector_tests) {
            ::testing::GTEST_FLAG(filter) = "VectorTest.*";
            RUN_ALL_TESTS();
        }
        if (run_map_tests) {
            ::testing::GTEST_FLAG(filter) = "MapTest.*";
            RUN_ALL_TESTS();
        }
        if (run_set_tests) {
            ::testing::GTEST_FLAG(filter) = "SetTest.*";
            RUN_ALL_TESTS();
        }
    }

    return 0;
}
