//
// Created by Denis Afendikov on 12.04.2021.
//

#include <iomanip>
#include <cmath>
#include "RPNInterpreter.h"
#include "exceptions/RunTimeError.h"
#include "../lexer/IntConstToken.h"
#include "../lexer/BoolConstToken.h"
#include "../lexer/RealConstToken.h"


const std::map<std::string, VariableType> RPNInterpreter::variableTypes = {
	{ "int", VariableType::INT },
	{ "real", VariableType::REAL },
	{ "bool", VariableType::BOOL }
};

bool RPNInterpreter::interpret( const std::vector<Lexer::LineToken>& tokens,
                                const std::vector<std::shared_ptr<IdentifierToken>>& identifiers ) {
	this->_tokens = tokens;
	this->_currToken = this->_tokens.begin();
	this->_identifiers = identifiers;
	this->global_stack = std::stack<Lexer::LineToken>{};
	try {
		return postfixProcessing();
	}
	catch (const RunTimeError& error) {
		std::cerr << error.what() << std::endl;
		if (_currToken != _tokens.end()) {
			std::cerr << "\t\t at " << std::setw(3) << _currToken->line
			          << " | \"" << std::prev(_currToken)->token->lexeme() << "\"" << std::endl;
		}
		return false;
	}
}

bool RPNInterpreter::postfixProcessing() {
	for (; _currToken != _tokens.end(); ++_currToken) {
		const Lexer::LineToken& token = *_currToken;
		if (token.token->is_one_of(Token::Identifier, Token::IntConst, Token::RealConst, Token::BoolConst)) {
			this->global_stack.push(token);
		}
		else {
			// Statements processing
			if (token.token->is(Token::Assign)) {
				// Assign final
				processAssign();
			}
			else if (
				token.token->is_one_of(
					Token::Add, Token::Sub, Token::Multiply,
					Token::Division, Token::IntDivision, Token::Power
				)) {
				processBinary();
			}
			else if (token.token->is(Token::Keyword)) {
				// variable initialization
				processInitialization();
			}
		}

	}
	return true;
}

void RPNInterpreter::processAssign() {
	Lexer::LineToken rvalue = global_stack.top();
	global_stack.pop();
	Lexer::LineToken lvalue = global_stack.top();
	global_stack.pop();

	if (lvalue.token->is_not(Token::Identifier)) {
		throw RunTimeError{ "lvalue required as left operand of assignment" };
	}
	std::shared_ptr<IdentifierToken> lvalueToken = std::dynamic_pointer_cast<IdentifierToken>(lvalue.token);
	lvalueToken->setActual(rvalue.token->actual(), rvalue.token->variableType());
}

void RPNInterpreter::processBinary() {
	// process binary operators
	Lexer::LineToken rightOp = global_stack.top();
	global_stack.pop();
	Lexer::LineToken leftOp = global_stack.top();
	global_stack.pop();

	if (leftOp.token->is(Token::Identifier)) {
		if (std::dynamic_pointer_cast<IdentifierToken>(leftOp.token)->variableType() == VariableType::UNDEFINED) {
			throw RunTimeError{ "Undefined variable" };
		}
	}

	if (rightOp.token->is(Token::Identifier)) {
		if (std::dynamic_pointer_cast<IdentifierToken>(rightOp.token)->variableType() == VariableType::UNDEFINED) {
			throw RunTimeError{ "Undefined variable" };
		}
	}

	std::shared_ptr<void> rightVal = rightOp.token->actual();
	std::shared_ptr<void> leftVal = leftOp.token->actual();
	Lexer::LineToken resVal{ leftOp.line };

	switch (_currToken->token->type()) {
	case Token::Add: {
		if (leftOp.token->variableType() == VariableType::INT
		    && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<IntConstToken>(
				*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				+ *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::INT
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				+ *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::INT
		         && rightOp.token->variableType() == VariableType::BOOL) {
			resVal.token = std::make_shared<IntConstToken>(
				*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				+ *std::static_pointer_cast<BoolConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				+ *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				+ *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::BOOL) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				+ *std::static_pointer_cast<BoolConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::BOOL
		         && rightOp.token->variableType() == VariableType::BOOL) {
			resVal.token = std::make_shared<BoolConstToken>(
				*std::static_pointer_cast<BoolConstToken::CTYPE>(leftVal)
				+ *std::static_pointer_cast<BoolConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::BOOL
		         && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<BoolConstToken>(
				*std::static_pointer_cast<BoolConstToken::CTYPE>(leftVal)
				+ *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::BOOL
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<BoolConstToken>(
				*std::static_pointer_cast<BoolConstToken::CTYPE>(leftVal)
				+ *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else {
			throw RunTimeError{ "Invalid operands for Add operation" };
		}
		break;
	}
	case Token::Sub: {
		if (leftOp.token->variableType() == VariableType::INT
		    && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<IntConstToken>(
				*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				- *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::INT
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				- *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::INT
		         && rightOp.token->variableType() == VariableType::BOOL) {
			resVal.token = std::make_shared<IntConstToken>(
				*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				- *std::static_pointer_cast<BoolConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				- *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				- *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::BOOL) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				- *std::static_pointer_cast<BoolConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::BOOL
		         && rightOp.token->variableType() == VariableType::BOOL) {
			resVal.token = std::make_shared<BoolConstToken>(
				*std::static_pointer_cast<BoolConstToken::CTYPE>(leftVal)
				- *std::static_pointer_cast<BoolConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::BOOL
		         && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<BoolConstToken>(
				*std::static_pointer_cast<BoolConstToken::CTYPE>(leftVal)
				- *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::BOOL
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<BoolConstToken>(
				*std::static_pointer_cast<BoolConstToken::CTYPE>(leftVal)
				- *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else {
			throw RunTimeError{ "Invalid operands for Subtract operation" };
		}
		break;
	}
	case Token::Multiply: {
		if (leftOp.token->variableType() == VariableType::INT
		    && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<IntConstToken>(
				*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				* *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::INT
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<RealConstToken>(
				(RealConstToken::CTYPE)*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				* *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::INT
		         && rightOp.token->variableType() == VariableType::BOOL) {
			resVal.token = std::make_shared<IntConstToken>(
				*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				* *std::static_pointer_cast<BoolConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				* *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				* (RealConstToken::CTYPE)*std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::BOOL) {
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				* *std::static_pointer_cast<BoolConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::BOOL
		         && rightOp.token->variableType() == VariableType::BOOL) {
			resVal.token = std::make_shared<BoolConstToken>(
				*std::static_pointer_cast<BoolConstToken::CTYPE>(leftVal)
				* *std::static_pointer_cast<BoolConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::BOOL
		         && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<BoolConstToken>(
				*std::static_pointer_cast<BoolConstToken::CTYPE>(leftVal)
				* *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::BOOL
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<BoolConstToken>(
				*std::static_pointer_cast<BoolConstToken::CTYPE>(leftVal)
				* *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else {
			throw RunTimeError{ "Invalid operands for Multiply operation" };
		}
		break;
	}
	case Token::Division: {
		if (leftOp.token->variableType() == VariableType::INT
		    && rightOp.token->variableType() == VariableType::INT) {
			if (*std::static_pointer_cast<IntConstToken::CTYPE>(rightVal) == 0) {
				throw RunTimeError{ "Division by 0" };
			}
			resVal.token = std::make_shared<RealConstToken>(
				(RealConstToken::CTYPE)*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				/ (RealConstToken::CTYPE)*std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::INT
		         && rightOp.token->variableType() == VariableType::REAL) {
			if (*std::static_pointer_cast<RealConstToken::CTYPE>(rightVal) == 0.0) {
				throw RunTimeError{ "Division by 0" };
			}
			resVal.token = std::make_shared<RealConstToken>(
				(RealConstToken::CTYPE)*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
				/ *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::REAL) {
			if (*std::static_pointer_cast<IntConstToken::CTYPE>(rightVal) == 0.0) {
				throw RunTimeError{ "Division by 0" };
			}
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				/ *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::INT) {
			if (*std::static_pointer_cast<IntConstToken::CTYPE>(rightVal) == 0) {
				throw RunTimeError{ "Division by 0" };
			}
			resVal.token = std::make_shared<RealConstToken>(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
				/ *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
			);
		}
		else {
			throw RunTimeError{ "Invalid operands for Division operation" };
		}
		break;
	}
	case Token::IntDivision: {
		if (leftOp.token->variableType() == VariableType::INT
		    && rightOp.token->variableType() == VariableType::INT) {
			if (*std::static_pointer_cast<IntConstToken::CTYPE>(rightVal) == 0) {
				throw RunTimeError{ "Division by 0" };
			}
			resVal.token = std::make_shared<IntConstToken>((IntConstToken::CTYPE)(
					*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
					/ *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
				)
			);
		}
		else if (leftOp.token->variableType() == VariableType::INT
		         && rightOp.token->variableType() == VariableType::REAL) {
			if (*std::static_pointer_cast<RealConstToken::CTYPE>(rightVal) == 0.0) {
				throw RunTimeError{ "Division by 0" };
			}
			resVal.token = std::make_shared<IntConstToken>((IntConstToken::CTYPE)(
					*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal)
					/ *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
				)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::REAL) {
			if (*std::static_pointer_cast<IntConstToken::CTYPE>(rightVal) == 0.0) {
				throw RunTimeError{ "Division by 0" };
			}
			resVal.token = std::make_shared<IntConstToken>((IntConstToken::CTYPE)(
					*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
					/ *std::static_pointer_cast<RealConstToken::CTYPE>(rightVal)
				)
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::INT) {
			if (*std::static_pointer_cast<IntConstToken::CTYPE>(rightVal) == 0) {
				throw RunTimeError{ "Division by 0" };
			}
			resVal.token = std::make_shared<IntConstToken>((IntConstToken::CTYPE)(
					*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal)
					/ *std::static_pointer_cast<IntConstToken::CTYPE>(rightVal)
				)
			);
		}
		else {
			throw RunTimeError{ "Invalid operands for IntDivision operation" };
		}
		break;
	}
	case Token::Power: {
		if (leftOp.token->variableType() == VariableType::INT
		    && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<IntConstToken>(pow(
				*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal),
				*std::static_pointer_cast<IntConstToken::CTYPE>(rightVal))
			);
		}
		else if (leftOp.token->variableType() == VariableType::INT
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<RealConstToken>(powl(
				*std::static_pointer_cast<IntConstToken::CTYPE>(leftVal),
				*std::static_pointer_cast<RealConstToken::CTYPE>(rightVal))
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::REAL) {
			resVal.token = std::make_shared<IntConstToken>(powl(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal),
				*std::static_pointer_cast<RealConstToken::CTYPE>(rightVal))
			);
		}
		else if (leftOp.token->variableType() == VariableType::REAL
		         && rightOp.token->variableType() == VariableType::INT) {
			resVal.token = std::make_shared<IntConstToken>(powl(
				*std::static_pointer_cast<RealConstToken::CTYPE>(leftVal),
				*std::static_pointer_cast<IntConstToken::CTYPE>(rightVal))
			);
		}
		else {
			throw RunTimeError{ "Invalid operands for Power operation" };
		}
		break;
	}
	default:
		throw RunTimeError{ "Unknown binary operator." };
	}
	global_stack.push(resVal);
}

void RPNInterpreter::processInitialization() {
	// next is Identifier
	std::shared_ptr<IdentifierToken> variable = std::dynamic_pointer_cast<IdentifierToken>(std::next(_currToken)->token);
	variable->setVariableType(variableTypes.at(_currToken->token->lexeme()));
}

const std::vector<std::shared_ptr<IdentifierToken>>& RPNInterpreter::getIdentifiers() const {
	return _identifiers;
}
