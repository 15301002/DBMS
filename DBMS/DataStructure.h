#pragma once

typedef int			INTEGER;
typedef bool		BOOL_;
typedef double		DOUBLE;
typedef char		VARCHAR[256];
typedef SYSTEMTIME	DATETIME;
typedef struct DATE_ {
	WORD wYear;
	WORD wMonth;
	WORD wDay;
}DATE_;

typedef struct Database{
	BOOL_		type;
	VARCHAR		name;
	DATETIME	creationTime;
	VARCHAR		filepath;
}Database;

typedef struct Table{
	VARCHAR name;
	INTEGER record_num;
	INTEGER field_num;
	VARCHAR tdf;
	VARCHAR trd;
	DATETIME crtime;
	DATETIME lmtime;
}Table;

typedef struct Field{
	VARCHAR name;
	INTEGER type;
	INTEGER param;
	DATETIME lmtime;
	INTEGER integrities;
}Field;