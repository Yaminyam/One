/**
 The One Programming Language

 File: ast/ast.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "ast.h"

int ident;

// char* ast_statement_name(AstStatementType type)
// {
// 	switch (type)
// 	{
// 		// case AST_GLOBAL_STATEMENT_FN:
// 		// 	return "FN";
// 		// case AST_GLOBAL_STATEMENT_VAR:
// 		// 	return "VAR";
// 		// case AST_GLOBAL_STATEMENT_ENUM:
// 		// 	return "ENUM";
// 		// case AST_GLOBAL_STATEMENT_STRUCT:
// 		// 	return "STRUCT";
// 		// case AST_GLOBAL_STATEMENT_TYPE:
// 		// 	return "TYPE";

// 		// case AST_STATEMENT_RET:
// 		// 	return "RET";
// 		// case AST_STATEMENT_PRINT:
// 		// 	return "PRINT";
// 		// case AST_STATEMENT_PRINTNL:
// 		// 	return "PRINTNL";
// 		// case AST_STATEMENT_PRINTDB:
// 		// 	return "PRINTDB";
// 		// case AST_STATEMENT_PRINTDBNL:
// 		// 	return "PRINTDBNL";

// 		// case AST_STATEMENT_WHILE:
// 		// 	return "WHILE";
// 		// case AST_STATEMENT_FOR:
// 		// 	return "FOR";
// 		// case AST_STATEMENT_DO:
// 		// 	return "DO";
// 		// case AST_STATEMENT_MATCH:
// 		// 	return "MATCH";

// 		// case AST_STATEMENT_EXPRESSION:
// 		// 	return "EXPRESSIONS";

// 		// case AST_STATEMENT_IF:
// 		// 	return "IF";

// 		// case AST_STATEMENT_VARIABLE:
// 		// 	return "VARIABLE";

// 		default:
// 			return "UNKNOWN";
// 	}
// }

// char* ast_value_name(AstValueType type)
// {
// 	switch (type)
// 	{
// 		// case AST_TYPE_I8:
// 		// 	return "i8";
// 		// case AST_TYPE_I16:
// 		// 	return "i16";
// 		// case AST_TYPE_I32:
// 		// 	return "i32";
// 		// case AST_TYPE_I64:
// 		// 	return "i64";
// 		// case AST_TYPE_I128:
// 		// 	return "i128";

// 		// case AST_TYPE_U8:
// 		// 	return "u8";
// 		// case AST_TYPE_U16:
// 		// 	return "u16";
// 		// case AST_TYPE_U32:
// 		// 	return "u32";
// 		// case AST_TYPE_U64:
// 		// 	return "u64";
// 		// case AST_TYPE_U128:
// 		// 	return "u128";

// 		// case AST_TYPE_F32:
// 		// 	return "f32";
// 		// case AST_TYPE_F64:
// 		// 	return "f64";

// 		// case AST_TYPE_STRING:
// 		// 	return "string";
// 		// case AST_TYPE_CHAR:
// 		// 	return "char";
// 		// case AST_TYPE_BOOL:
// 		// 	return "bool";

// 		default:
// 			return "UNKNOWN";
// 	}
// }

void ast_init(const char* input_file, const char* data, Token** tokens, AstFile* ast)
{
	ident = 0;
}

void ast_trace_ident(FILE* file_out)
{
	if(ident == 0) return;
	char* idents = malloc(sizeof(char)*(ident*2)+1);

	for(int i=0; i< ident*2; i++)
		idents[i] = ' ';

	fprintf(file_out, idents);
}

void ast_trace_ident_next()
{
	ident++;
}

void ast_trace_ident_prev()
{
	ident--;
}

void ast_trace_imports(FILE* file_out, AstImportDeclarationArray* imports)
{

	AstImportDeclaration* name_item;

	ast_trace_ident(file_out);
	fprintf(file_out, "Imports (%d) [\n", imports->count);

	ast_trace_ident_next();

	for (int i = 0; i < imports->count; i++)
	{
		name_item = (AstImportDeclaration*)imports->data[i];
		ast_trace_import(file_out, name_item);
	}

	ast_trace_ident_prev();
	fprintf(file_out, "]\n");
}

void ast_trace_import_name(FILE* file_out, AstImportName* name)
{
	fprintf(file_out, "%s", name->name);
}

void ast_trace_import_names(FILE* file_out, AstImportNameArray* names)
{
	AstImportName* name;

	ast_trace_ident(file_out);
	fprintf(file_out, "Names = (%d) [ ", names->count);
	for (int i = 0; i < names->count; i++)
	{
		name = (AstImportName*)names->data[i];
		ast_trace_import_name(file_out, name);
		if (i + 1 != names->count)
		{
			fprintf(file_out, "->");
		}
	}
	fprintf(file_out, " ]\n");
}

void ast_trace_import(FILE* file_out, AstImportDeclaration* import)
{
	AstImportSymbol* symbol_item;

	AstImportName* name;
	AstImportSymbol* symbol;

	AstImportNameArray* names;
	AstImportSymbolArray* symbols;

	ast_trace_ident(file_out);
	fprintf(file_out, "\tImport {\n");
	ast_trace_ident_next();

	names = import->names;
	ast_trace_import_names(file_out, names);

	ast_trace_ident(file_out);
	fprintf(file_out, "Alias = %s\n", import->alias == NULL ? "none" : import->alias);

	symbols = import->symbols;

	ast_trace_ident(file_out);
	fprintf(file_out, "Symbols = (%d) [", symbols->count);

	fprintf(file_out, "\n");
	for (int i = 0; i < symbols->count; i++)
	{
		symbol = (AstImportSymbol*)symbols->data[i];

		names = (AstImportNameArray*)symbol->names;
		ast_trace_import_names(file_out, names);

		fprintf(file_out, "Alias = %s", symbol->has_alias ? symbol->alias : "None");
		fprintf(file_out, " }\n");
	}
	fprintf(file_out, "\t\t]\n");

	fprintf(file_out, "\t}\n");
}

void ast_trace(FILE* file_out, AstFile* ast)
{
	fprintf(file_out, "Program %s (%s)\n", ast->path, ast->path_base);
	fprintf(file_out, "Module %s\n", (ast->module->name != NULL) ? ast->module->name : "none");

	ast_trace_imports(file_out, ast->imports);
}

void ast_free()
{
}
