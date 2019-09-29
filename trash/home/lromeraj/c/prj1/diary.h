#ifndef DIARY_H

  #define DIARY_H

  #define MAX_C 100 // max contact list size
  #define MAX_S 30 // max string size

  typedef struct {
    char name[MAX_S], name2[MAX_S];
    int phone;
  } Contact;

  typedef struct {
    Contact list[MAX_C];
    char f_name[MAX_S];
    int size;
  } Diary;

#endif

void add_contact( Diary*, Contact );
int load_diary( Diary* );
int find( Diary, char* );
