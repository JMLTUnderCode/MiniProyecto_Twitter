{
module Lexer where
}

%wrapper "basic"

$digit = 0-9
$alpha = [a-zA-Z]
$backslash = \92 
$slash = [\/] 
$canvas = [ \\ \_ \/ \"empty" \|]
-- ksakasakk

tokens :-
  $white+         ;
  $digit+               { \s -> TkNumLit (stringToInt s )}

  \< + $canvas + >      { \s -> TkCanvasList s}
  \,                    { \s -> TkComa }
  \;                    { \s -> TkPuntoYComa }
  \(                    { \s -> TkParAbre }
  \)                    { \s -> TkParCierra }
  \+                    { \s -> TkMas }
  \-                    { \s -> TkMenos}
  \*                    { \s -> TkMult}
  \/                    { \s -> TkDiv}
  \%                    { \s -> TkMod }
  $slash+ $backslash    { \s -> TkConjuncion}
  $backslash+ $slash    { \s -> TkDisyuncion }
  \^                    { \s -> TkNegacion }
  \<                    { \s -> TkMenor }
  \<+=                  { \s -> TkMenorIgual }
  \>                    { \s -> TkMayor }
  \>+=                  { \s -> TkMayorIgual }
  =                     { \s -> TkIgual}
  \/+=                  { \s -> TkDesigual }
  \:+ =                 { \s -> TkAsignacion}
  \:                    { \s -> TkConcatHorizontal }
  \|                    { \s -> TkConcatVertical }
  \$                    { \s -> TkRotacion }
  \'                    { \s -> TkTransposicion }
  "True"                { \s -> TkTrue  }
  "False"               { \s -> TkFalse  }
  "if"                  { \s -> TkIf }
  "using"               { \s -> TkUsing }
  "repeat"              { \s -> TkRepeat }
  "begin"               { \s -> TkBegin }
  "end"                 { \s -> TkEnd }
  
  $alpha+               { \s -> TkIdent s }

{

stringToInt :: String -> Int
stringToInt s = read s

data Token = TkNumLit Int
            | TkIdent String
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
            | TkTrue 
            | TkFalse
            | TkIf
            | TkUsing
            | TkRepeat
            | TkBegin
            | TkEnd
            | TkCanvasList String
     
             deriving (Eq,Show)
}