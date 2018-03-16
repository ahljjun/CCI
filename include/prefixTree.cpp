#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cassert>

using std::string;
using std::stack;

template <class T>
struct TreeNode {
	TreeNode(T value): data(value), left(0), right(0) {}
	T data;
	TreeNode *left;
	TreeNode *right;
};

typedef TreeNode<string>  strTreeNode;

std::vector<string> split(const string& s, const string& delim)
{
	std::vector<string> strVec;

	std::string::size_type pos1, pos2;
	pos2 = s.find(delim);
	pos1 = 0;
	while( std::string::npos != pos2 )
	{
		strVec.push_back(s.substr(pos1, pos2-pos1));
		pos1 = pos2 + delim.size();
        pos2 = s.find(delim, pos1);
	}

	if ( pos1 != s.length() )
		strVec.push_back(s.substr(pos1));

	return strVec;
}

bool isOperator(const string& s)
{
	return s == "+" || s == "-" || s == "*" || s == "/" ;
}

bool isParentheses(const string& s)
{
	return s == "(" || s == ")" ;
}

bool comparePriority(const string& s1, const string& s2)
{
	std::cout<<"comparePriority: s1: "<<s1<<", s2: "<<s2<<std::endl;
	if ( s1 == "*" || s1 == "/" )
	{
		if ( s2 == "+" || s2 == "-" )
		{
			return true;
		} 
	}
	else
	{
		return false; 
	}

	return true;
}

TreeNode<string>*
convertToPrefixTree(const string &expression) 
{
	//suppose the expression is prefix expression and split by " "
	std::vector<string> strVec = split(expression, " ");
	//std::copy(strVec.begin(), strVec.end(), std::ostream_iterator<string>(std::cout, "\n"));
	stack<TreeNode<string>* > NodeStack;

	for(int i = strVec.size()-1; i >=0 ; i--)
	{
		TreeNode<string>* node = new TreeNode<string>(strVec[i]);
		if ( isOperator(strVec[i]) ) // this is operator
		{
			TreeNode<string>* leftNode = NodeStack.top();
			NodeStack.pop();
			TreeNode<string>* rightNode = NodeStack.top();
			NodeStack.pop();

			node->left = leftNode;
			node->right = rightNode;
		}

		NodeStack.push(node);
	}

	TreeNode<string>* root = 0;
	if ( ! NodeStack.empty() )
	{
		root = NodeStack.top();	
		NodeStack.pop();	
	}

	assert(NodeStack.empty());
	return root;
}

// post-fix string to post-fix tree
TreeNode<string>*
convertToPostTree(const string &expression) 
{
	//suppose the expression is prefix expression and split by " "
	std::vector<string> strVec = split(expression, " ");
	//std::copy(strVec.begin(), strVec.end(), std::ostream_iterator<string>(std::cout, "\n"));
	stack<TreeNode<string>* > NodeStack;

	for(int i=0; i < strVec.size(); i++)
	{
		TreeNode<string>* node = new TreeNode<string>(strVec[i]);
		if ( isOperator(strVec[i]) ) // this is operator
		{
			TreeNode<string>* leftNode = NodeStack.top();
			NodeStack.pop();
			TreeNode<string>* rightNode = NodeStack.top();
			NodeStack.pop();

			node->left = leftNode;
			node->right = rightNode;
		}

		NodeStack.push(node);
	}

	TreeNode<string>* root = 0;
	if ( ! NodeStack.empty() )
	{
		root = NodeStack.top();	
		NodeStack.pop();	
	}

	assert(NodeStack.empty());
	return root;
}


void convertToReversePolishNotation(const string& expression)
{
	//suppose the expression is prefix expression and split by " "
	std::vector<string> strVec = split(expression, " ");
	std::copy(strVec.begin(), strVec.end(), std::ostream_iterator<string>(std::cout, " "));
	std::cout<<" strVec "<<std::endl;

	stack<string> OpStack;
	stack<string> tmpStack;

	for(int i=0; i < strVec.size(); i++)
	{
		if ( isOperator(strVec[i]) )
		{
			while(!OpStack.empty() 
				    && (OpStack.top() != "(")
				    && !comparePriority(strVec[i], OpStack.top()))
			{
				tmpStack.push(OpStack.top());
				OpStack.pop();
			}

			OpStack.push(strVec[i]);
		}
		else if ( isParentheses(strVec[i]) )
		{
			if ( strVec[i]== "(" )
			{
				OpStack.push(strVec[i]);
			}
			else // is ")"
			{
				while( !OpStack.empty() && OpStack.top() != "(" )
				{
					tmpStack.push(OpStack.top());
					OpStack.pop();
				}
				if ( OpStack.empty() || OpStack.top() != "(" )
				{
					std::cerr<< "Parentheses is not matched" << std::endl;
					return ;
				}

				OpStack.pop(); // clear this "()"
			}
		}
		else // the data now
		{
			tmpStack.push(strVec[i]);
		}
	}


    //assert(!OpStack.empty());
    //1 2 3 + 4 × + 5 -

	while(!tmpStack.empty())
	{
		OpStack.push(tmpStack.top());

		tmpStack.pop();
	}

	while(!OpStack.empty())
	{
		std::cout<<OpStack.top()<<" " ;
		OpStack.pop();
	}

	std::cout<<"\n";
}


template <class T>
void printTree(TreeNode<T>* root)
{
	if (!root){
		return;
	}
 
	printTree(root->left);
	printTree(root->right);
    std::cout<< root->data << " ";
}


int main()
{
	const string preExpression = "* + 2 4 2";
	TreeNode<string>* tree = convertToPrefixTree(preExpression);

    printTree(tree);

    std::cout<<"convertToReversePolishNotation begins===="<<std::endl;

    const string midExpression = "1 + ( ( 2 + 3 ) * 4 ) - 5";
    convertToReversePolishNotation(midExpression);

    std::cout<<"convertToReversePolishNotation ends===="<<std::endl;
    return 0;
}




