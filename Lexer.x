{
module Lexer where
}

%wrapper "basic"

$digit = 0-9

$backslash = [\\] 
$slash = [\/] 
$equal = [\=] 

tokens :-
  $white+         ;
  $digit+          { \s -> TkNumLit (stringToInt s )}
  \,               { \s -> TkComa }
  \;               { \s -> TkPuntoYComa }
  \(               { \s -> TkParAbre }
  \)               { \s -> TkParCierra }
  \+               { \s -> TkMas }
  \-               { \s -> TkMenos}
  \*               { \s -> TkMult}
  \/               { \s -> TkDiv}
  \%               { \s -> TkMod }
  $slash+ $backslash  { \s -> TkConjuncion}
  $backslash+ $slash    { \s -> TkDisyuncion }
  \^               { \s -> TkNegacion }
  \<               { \s -> TkMenor }
  \<+$equal        { \s -> TkMenorIgual }
  \>               { \s -> TkMayor }
  \>+$equal        { \s -> TkMayorIgual }
  $equal           { \s -> TkIgual}
  \/+$equal        { \s -> TkDesigual }
  \:+ $equal       { \s -> TkAsignacion}
  \:               { \s -> TkConcatHorizontal }
  \|               { \s -> TkConcatVertical }
  \$               { \s -> TkRotacion }
  \'               { \s -> TkTransposicion }

{

stringToInt :: String -> Int
stringToInt s = read s

data Token = TkNumLit Int
            | TkComa
            | TkPuntoYComa
            | TkParAbre
            | TkParCierra
            | TkMas
            | TkMenos
            | TkMult
            | TkDiv
            | TkMod
            | TkConjuncion
            | TkDisyuncion
            | TkNegacion
            | TkMenor
            | TkMenorIgual
            | TkMayor
            | TkMayorIgual
            | TkIgual
            | TkDesigual
            | TkConcatHorizontal
            | TkConcatVertical
            | TkRotacion
            | TkTransposicion
            | TkAsignacion
     
             deriving (Eq,Show)
}