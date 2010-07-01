#include "headers/Show.h"

Show::Show ( const string& n ): 
		name(n) {
	anime_list = new vector<Anime*>();
	status = NOT_WATCHING;
}

Show::Show( const Show& s ) {
	name = s.name;
	anime_list = new vector<Anime*>( *s.anime_list );
	next = anime_list->begin() + distance( s.anime_list->begin(), s.next );
	status = s.status;
}

Show::~Show () {
	anime_list->clear();
	delete(anime_list);
}

Show& Show::operator=( const Show& s ) {
	if( this == &s )
		return *this;
	name = s.name;
	anime_list = new vector<Anime*>( *s.anime_list );
	next = anime_list->begin() + distance( s.anime_list->begin(), s.next );
	status = s.status;
	return *this;
}

ostream& operator<<( ostream& output,const Show& s ) {
	output << s.name << endl <<
	  	distance( s.anime_list->begin(), s.next ) << " " <<  
		distance( s.anime_list->begin(), s.anime_list->end() ) << endl;
	vector<Anime*>::const_iterator it;
	for( it = (s.anime_list)->begin(); it < (s.anime_list)->end() - 1; ++it );
		output << (*it)->print();
	return output;
}

void Show::add ( Anime& a ) {	
	int old = anime_list->size();
	int pos = distance( anime_list->begin(), next );
	anime_list->reserve( old + 1 );
	anime_list->push_back( &a );
	if( old == 0 )
		next = anime_list->begin();
	else
		next = anime_list->begin() + pos;
}

void Show::incNext() {
	if( next < anime_list->end() )
		++next;
	else if( next == anime_list->end() ) {
		next = anime_list->begin();
		status = COMPLETED;
	}
}

void Show::playIndex( const int& i ) {
	vector<Anime*>::iterator it = anime_list->begin() + (i - 1);
	(*it)->playNext();
}

void Show::playNext() {
	status = WATCHING;
	if( (*next)->playNext() )
		incNext();
}

const string& Show::print() const {
	string *str = new string();
	int cur = 0,
		 tot = 0;

	vector<Anime*>::const_iterator cit;
	for( cit = anime_list->begin(); cit < anime_list->end(); ++cit ) {
		cur += (*cit)->getCurrent();
		tot += (*cit)->getTotal();
	}

	stringstream o;
	o << "[" << cur << "/" << tot << "] " << name;
	*str = o.str();

	return *str;
}

const string& Show::printName() const {
	return name;
}

void Show::unPlay() {
	if( (*next)->unPlay() == false )
		if( next > anime_list->begin() )
			--next;
}
