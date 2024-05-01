#pragma one
#include <iostream>
#include <cstddef>
#include "Sequence.h"
#include "DynamicArraySequence.h"
#include "LinkedListSequence.h"
#include "AbstractActionListener.h"

using namespace std;

template <class T>
class MutableActionHandler : public AbstractActionListener<T>
{
private:
    Sequence<T> *working_sequence;

public:
    MutableActionHandler() : working_sequence{nullptr} {};

    ~MutableActionHandler()
    {
        delete[] working_sequence;
    }
    MutableActionHandler<T> *create_sequence_dialog() override
    {
        cout << "1 - to create Mutable Dynamic Array Sequence\n2 - to create Mutable Linked List Sequence\n-1 - to return\n->";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            return create_dynamic_array_sequence();
            break;
        case 2:
            return create_linked_list_sequence();
            break;
        default:
            return this;
            break;
        }
    }

    MutableActionHandler<T> *create_linked_list_sequence() override
    {
        cout << "Creating Linked List Sequence\nenter size of sequence->";
        int n;
        cin >> n;
        T data[n];
        cout << "Enter " << n << " elements of future array\n->";
        for (int i = 0; i < n; i++)
        {
            cin >> data[i];
        }

        LinkedListSequence<T> *linked_list = new LinkedListSequence(data, n);
        working_sequence = linked_list;
        return this;
    }

    MutableActionHandler<T> *create_dynamic_array_sequence() override
    {
        cout << "Creating Dynamic Array Sequence\nenter size of sequence->";
        int n;
        cin >> n;
        T data[n];
        cout << "Enter " << n << " elements of future list\n->";
        for (int i = 0; i < n; i++)
        {
            cin >> data[i];
        }

        DynamicArraySequence<T> * dynamic_array = new DynamicArraySequence(data, n);
        working_sequence = dynamic_array;
        return this;
    }
    MutableActionHandler<T> *get_n_show_subsequence() override
    {
        cout << "Extracting subsequence\n Enter start index and end index [start index, end index]\n->";
        size_t start_index, end_index;
        cin >> start_index >> end_index;
        Sequence<T> *subsequence;
        try
        {
            subsequence = working_sequence->get_subsequence(start_index, end_index);
            for (size_t i = 0; i < subsequence->get_length() ; i++)
            {
                cout << subsequence->get(i) << " ";
            }
        }
        catch(const std::exception& e)
        {
            cout << "Exception occurred, something goes wrong: " << e.what() << '\n';
            return this;
        }
        return this;
    }
    MutableActionHandler<T> *add_element_to_begin() override
    {
        cout << "Adding element to begin of sequence\n";
        if (working_sequence == nullptr)
        {
            cout << "Can not add element because not any sequence created";
            return this;
        }
        cout << "Enter element with the same declaration type\n->";
        T elem;
        cin >> elem;
        working_sequence->prepend(elem);
        return this;
    }
    MutableActionHandler<T> *add_element_to_position() override
    {
        cout << "Adding element to mentioned position\n";
        if (working_sequence == nullptr)
        {
            cout << "Can not add element because not any sequence created";
            return this;
        }
        int position;
        cout << "Enter position\n->";
        cin >> position;
        cout << "Enter element with the same declaration type\n->";
        T elem;
        cin >> elem;
        working_sequence->insert_at(position, elem);
        return this;
    }
    MutableActionHandler<T> *add_element_to_end() override
    {
        cout << "Adding element to end of sequence\n";
        if (working_sequence == nullptr)
        {
            cout << "Can not add element because not any sequence created";
            return this;
        }
        cout << "Enter element with the same declaration type\n->";
        T elem;
        cin >> elem;
        working_sequence->append(elem);
        return this;
    }
    MutableActionHandler<T> *print_working_sequence() override
    {
        if (working_sequence == nullptr)
        {
            cout << "Can not add element because not any sequence created\n";
            return this;
        }
        cout << "Printing working sequence...\n->";
        for (size_t i = 0; i < working_sequence->get_length(); i++)
        {
            cout << working_sequence->get(i) << " ";
        }
        cout << "\n";
        return this;
    }
    MutableActionHandler<T> *concat_with_new_sequence() override
    {
        MutableActionHandler<T> new_action_handler;
        new_action_handler.create_sequence_dialog();
        working_sequence->concat(new_action_handler.working_sequence);
        return this;
    }
};
