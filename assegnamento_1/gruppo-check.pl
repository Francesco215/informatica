#!/usr/bin/perl -w
use strict;

my $i=0;
print "Gruppo\n";
while ( my $l = <> ) {
    $i++;
    print "  Membro $i:\n";
    chomp $l;
    my @a=split ",",$l;
    ( $a[0] =~ /^\s*([[:alpha:] \']+)\s*$/ )
    || die "Errore $a[0]: solo caratteri alfabetici nel cognome\n";
    print "    COGNOME: -$1-\n";
    ( $a[1] =~ /^\s*([[:alpha:] ]+)\s*$/ )
    || die "Errore $a[1]: solo caratteri alfabetici nel nome\n";
    print "    NOME: -$1-\n";
    ( $a[2] =~ /^\s*([[:digit:]]+)\s*$/ ) 
    || die "Errore $a[2]: solo cifre nel n. di matricola\n";
    print "    MATRICOLA: -$1-\n";
    print "    EMAIL: -$a[3]-\n";
}

( $i > 2 ) 
    && die "Attenzione: al massimo 2 membri per gruppo!\n"
