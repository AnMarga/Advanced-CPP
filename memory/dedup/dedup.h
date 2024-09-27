#pragma once

#include <memory>
#include <vector>
#include <string>

using std::string;

std::vector<std::unique_ptr<string>> Duplicate(const std::vector<std::shared_ptr<string>>& items) {
    std::vector<std::unique_ptr<string>> out(items.size());
    // массив items это вектор указателей shared_ptr
    // нам необходимо преобразовать их в уникальные unique_ptr и вернуть вектор out
    //*items[i] - значение объекта
    //  items[i] - адрес объекта

    /*
    Здесь всё просто: для каждого элемента из items заводим новый unique_ptr
    и добавляем на i-ю позицию в out
    */

    // цикл, бегает по всем элементам из items
    for (size_t i = 0; i < items.size(); ++i) {
        // std::unique_ptr<string> u_ptr = std::make_unique<string>(*items[i]);
        out[i] = std::make_unique<string>(*items[i]);
    }
    return out;
}

std::vector<std::shared_ptr<string>> DeDuplicate(
    const std::vector<std::unique_ptr<string>>& items) {

    std::vector<std::shared_ptr<string>> out(items.size());
    // массив items это вектор уникальных указателей unique_ptr
    // нам необходимо преобразовать их в shared_ptr и вернуть вектор out
    //*items[i] - значение объекта
    //  items[i] - адрес объекта

    /*
    Берём элемент из items
    Нужно убедиться, что его ещё нет в векторе out:
    1) если его нет, то создаём новый shared_ptr и добавляем его в out
    2) если он есть, то создаём указатель типа shared_ptr и приравниваем его
       к первому встретившемуся shared_ptr, указывающему на то же значение
    */

    // цикл, бегает по всем элементам из items
    for (size_t i = 0; i < items.size(); ++i) {
        bool flag = false;  // флаг: false - элемент больше не встречался, true - встречался
        int index = 0;  // индекс самого раннего встретившегося элемент

        // проверяем циклом, есть ли уже items[i] в out
        std::vector<int> vec_of_indexes;
        for (size_t j = 0; j < i; ++j) {
            if (*out[j] == *items[i]) {
                flag = true;
                vec_of_indexes.push_back(j);
            }
        }
        if (flag) {
            index = vec_of_indexes[0];
        }

        if (flag) {
            // если такой уже есть, то просто приводим наш unique_ptr к
            //  shared_ptr и добавляем на i-ю позицию в out
            out[i] = out[index];
        } else {
            // если такого ещё нет, то создаём новый указатель типа shared_ptr и
            // передаём ему значение объекта, на который указывает unique_ptr
            // затем добавляем в out на i-ю позицию
            out[i] = std::make_shared<string>(*items[i]);
        }
    }

    return out;
}
