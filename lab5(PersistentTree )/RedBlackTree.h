//
// Created by Acer on 14.03.2021.
//

#ifndef LAB5_PERSISTENTTREE_REDBLACKTREE_H
#define LAB5_PERSISTENTTREE_REDBLACKTREE_H


#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

typedef enum {BLACK, RED} nodeColor;

class Tree {
private:
    class Node {

    public:
        Node *_left;
        Node *_right;
        Node *_parent;
        nodeColor _color;
        int _data;

        explicit Node(int data);
        Node(Node* node, Node* parent); // care, changes parent of node's sons to this

        [[nodiscard]] int max_depth() const {
            const int left_depth = _left ? _left->max_depth() : 0;
            const int right_depth = _right ? _right->max_depth() : 0;
            return (left_depth > right_depth ? left_depth : right_depth) + 1;
        }

        void output(Node *node, int space) const;
    };

    [[nodiscard]] int get_max_depth() const { return root ? root->max_depth() : 0; }

    void clearMemory(Node* node);

    void fixInsertion(Node* node);// creates new nodes
    void fixErasing(Node* node);  // creates new nodes

    void leftRotate(Node* node);  // creates new nodes
    void rightRotate(Node* node); // creates new nodes

    void erase(Node* node);

    void backUpTree(Node* node);

private:
    Node* root;

public:
    vector<Node*> previousRoots;

public:
    Tree();
    explicit Tree(Node* root);
    ~Tree();

    [[nodiscard]] Node* getSuccessor(Node* node); // has getMinNode which creates new nodes
    [[nodiscard]] Node* getMinNode(Node* node) const; //creates new nodes

    [[nodiscard]] Node* search(int data); //creates new nodes

    void insert(int data); // creates new nodes
    void erase(int data);  // creates new nodes

    void backUpPreviousRoot(Node* newRoot);

    void output() const;
    void DumpAllRoots();

    //next code was copyrighted from
    //https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
    struct cell_display {
        string   valstr;
        bool     present;
        cell_display() : present(false) {}
        cell_display(std::string valstr) : valstr(valstr), present(true) {}
    };
    using display_rows = vector< vector< cell_display > >;
    display_rows get_row_display() const {
        vector<Node*> traversal_stack;
        vector< std::vector<Node*> > rows;
        if(!root)
            return display_rows();

        Node *p = root;
        const int max_depth = root->max_depth();
        rows.resize(max_depth);
        int depth = 0;
        for(;;) {
            if(depth == max_depth-1) {
                rows[depth].push_back(p);
                if(depth == 0) break;
                --depth;
                continue;
            }

            if(traversal_stack.size() == depth) {
                rows[depth].push_back(p);
                traversal_stack.push_back(p);
                if(p) p = p->_left;
                ++depth;
                continue;
            }

            if(rows[depth+1].size() % 2) {
                p = traversal_stack.back();
                if(p) p = p->_right;
                ++depth;
                continue;
            }

            if(depth == 0) break;

            traversal_stack.pop_back();
            p = traversal_stack.back();
            --depth;
        }

        display_rows rows_disp;
        std::stringstream ss;
        for(const auto& row : rows) {
            rows_disp.emplace_back();
            for(Node* pn : row) {
                if(pn) {
                    ss << pn->_data << ":";
                    if (pn->_color == RED)
                        ss << "R:";
                    else
                        ss << "B:";
                    ss << pn;
                    rows_disp.back().push_back(cell_display(ss.str()));
                    ss = std::stringstream();
                } else {
                    rows_disp.back().push_back(cell_display());
                }   }   }
        return rows_disp;
    }
    vector<string> row_formatter(const display_rows& rows_disp) const {
        using s_t = string::size_type;

        s_t cell_width = 0;
        for(const auto& row_disp : rows_disp) {
            for(const auto& cd : row_disp) {
                if(cd.present && cd.valstr.length() > cell_width) {
                    cell_width = cd.valstr.length();
                }   }   }

        if(cell_width % 2 == 0) ++cell_width;

        vector<string> formatted_rows;

        s_t row_count = rows_disp.size();

        s_t row_elem_count = 1 << (row_count-1);

        s_t left_pad = 0;

        for(s_t r=0; r<row_count; ++r) {
            const auto& cd_row = rows_disp[row_count-r-1];
            s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
            string row;
            for(s_t c=0; c<row_elem_count; ++c) {
                row += string(c ? left_pad*2+1 : left_pad, ' ');
                if(cd_row[c].present) {
                    const string& valstr = cd_row[c].valstr;
                    s_t long_padding = cell_width - valstr.length();
                    s_t short_padding = long_padding / 2;
                    long_padding -= short_padding;
                    row += string(c%2 ? short_padding : long_padding, ' ');
                    row += valstr;
                    row += string(c%2 ? long_padding : short_padding, ' ');
                } else {
                    row += string(cell_width, ' ');
                }
            }

            formatted_rows.push_back(row);

            if(row_elem_count == 1) break;

            s_t left_space  = space + 1;
            s_t right_space = space - 1;
            for(s_t sr=0; sr<space; ++sr) {
                string row;
                for(s_t c=0; c<row_elem_count; ++c) {
                    if(c % 2 == 0) {
                        row += string(c ? left_space*2 + 1 : left_space, ' ');
                        row += cd_row[c].present ? '/' : ' ';
                        row += string(right_space + 1, ' ');
                    } else {
                        row += string(right_space, ' ');
                        row += cd_row[c].present ? '\\' : ' ';
                    }
                }
                formatted_rows.push_back(row);
                ++left_space;
                --right_space;
            }
            left_pad += space + 1;
            row_elem_count /= 2;
        }

        std::reverse(formatted_rows.begin(), formatted_rows.end());

        return formatted_rows;
    }
    static void trim_rows_left(vector<string>& rows) {
        if(!rows.size()) return;
        auto min_space = rows.front().length();
        for(const auto& row : rows) {
            auto i = row.find_first_not_of(' ');
            if(i==string::npos) i = row.length();
            if(i == 0) return;
            if(i < min_space) min_space = i;
        }
        for(auto& row : rows) {
            row.erase(0, min_space);
        }   }
    void Dump() const {
        const int d = get_max_depth();

        // If this tree is empty, tell someone
        if(d == 0) {
            cout << " <empty tree>\n";
            return;
        }

        const auto rows_disp = get_row_display();

        auto formatted_rows = row_formatter(rows_disp);

        trim_rows_left(formatted_rows);
        for(const auto& row : formatted_rows) {
            std::cout << ' ' << row << '\n';
        }
    }

};


#endif //LAB5_PERSISTENTTREE_REDBLACKTREE_H
