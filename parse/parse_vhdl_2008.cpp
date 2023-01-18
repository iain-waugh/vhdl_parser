//
//  parse_vhdl_2008.cpp
//
//  Cross platform VHDL 2008 parser
//
//  MIT License
//
//  Copyright (C) 2022-2023 Iain Waugh. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "peglib.h"

inline bool read_file(const fs::path file_path, vector<char> &buffer) {
  ifstream ifs(file_path, ios::in | ios::binary);
  if (ifs.fail())
  {
      return false;
  }

  buffer.resize(static_cast<unsigned int>(ifs.seekg(0, ios::end).tellg()));
  if (!buffer.empty()) {
    ifs.seekg(0, ios::beg).read(&buffer[0], static_cast<streamsize>(buffer.size()));
  }
  return true;
}

int parse_vhdl_2008(fs::path hdl_file_path) {
  // Make a parser using the peglib "parser" method
  peg::parser parser(R"(

# VHDL-2008 grammar based on IEEE 1076-12008
# Standard note:
#  { } means 0 or more times
#  [ ] means 1 or more times
vhdl2008 <-  Spacing? design_file EndOfFile
Spacing <- (Space / Comment)*
Space <- ' ' / '\t' / EndOfLine
EndOfLine <- '\r\n' / '\n' / '\r'
EndOfFile <- !.
~_     <- ( Comment / Space )*
%whitespace <- _

# ------------------------------------------------------------------------
# Comments : Section 15.9
Comment <- Comment_93 / Comment_2008
Comment_93 <- '--' (!EndOfLine . )* EndOfLine
Comment_2008 <- "/*" (!"*/" .)* "*/"

# ------------------------------------------------------------------------
# Reserved words : Section 15.10
_abs          <- < 'abs'i delimiter >
_access       <- < 'access'i delimiter >
_after        <- < 'after'i delimiter >
_alias        <- < 'alias'i delimiter >
_all          <- < 'all'i delimiter >
_and          <- < 'and'i delimiter >
_architecture <- < 'architecture'i delimiter >
_array        <- < 'array'i delimiter >
_assert       <- < 'assert'i delimiter >  # Part of PSL now, but listed here because it's always been in VHDL
_attribute    <- < 'attribute'i delimiter >
_begin        <- < 'begin'i delimiter >
_block        <- < 'block'i delimiter >
_body         <- < 'body'i delimiter >
_buffer       <- < 'buffer'i delimiter >
_bus          <- < 'bus'i delimiter >
_case         <- < 'case'i delimiter >
_component    <- < 'component'i delimiter >
_configuration <- < 'configuration'i delimiter >
_constant     <- < 'constant'i delimiter >
_context      <- < 'context'i  delimiter ># VHDL-2008 only
_disconnect   <- < 'disconnect'i delimiter >
_downto       <- < 'downto'i delimiter >
_else         <- < 'else'i delimiter >
_elsif        <- < 'elsif'i delimiter >
_end          <- < 'end'i delimiter >
_entity       <- < 'entity'i delimiter >
_exit         <- < 'exit'i delimiter >
_file         <- < 'file'i delimiter >
_for          <- < 'for'i delimiter >
_force        <- < 'force'i  delimiter > # VHDL-2008 only
_function     <- < 'function'i delimiter >
_generate     <- < 'generate'i delimiter >
_generic      <- < 'generic'i delimiter >
_group        <- < 'group'i delimiter >
_guarded      <- < 'guarded'i delimiter >
_if           <- < 'if'i delimiter >
_impure       <- < 'impure'i delimiter >
_in           <- < 'in'i delimiter >
_inertial     <- < 'inertial'i delimiter >
_inout        <- < 'inout'i delimiter >
_is           <- < 'is'i delimiter >
_label        <- < 'label'i delimiter >
_library      <- < 'library'i delimiter >
_linkage      <- < 'linkage'i delimiter >
_literal      <- < 'literal'i delimiter >
_loop         <- < 'loop'i delimiter >
_map          <- < 'map'i delimiter >
_mod          <- < 'mod'i delimiter >
_nand         <- < 'nand'i delimiter >
_new          <- < 'new'i delimiter >
_next         <- < 'next'i delimiter >
_nor          <- < 'nor'i delimiter >
_not          <- < 'not'i delimiter >
_null         <- < 'null'i delimiter >
_of           <- < 'of'i delimiter >
_on           <- < 'on'i delimiter >
_open         <- < 'open'i delimiter >
_or           <- < 'or'i delimiter >
_others       <- < 'others'i delimiter >
_out          <- < 'out'i delimiter >
_package      <- < 'package'i delimiter >
_parameter    <- < 'parameter'i delimiter >  # VHDL-2008 only
_port         <- < 'port'i delimiter >
_postponed    <- < 'postponed'i delimiter >
_procedure    <- < 'procedure'i delimiter >
_process      <- < 'process'i delimiter >
_protected    <- < 'protected'i delimiter >  # VHDL-2008 only
_pure         <- < 'pure'i delimiter >
_range        <- < 'range'i delimiter >
_record       <- < 'record'i delimiter >
_register     <- < 'register'i delimiter >
_reject       <- < 'reject'i delimiter >
_release      <- < 'release'i delimiter >  # VHDL-2008 only
_rem          <- < 'rem'i delimiter >
_report       <- < 'report'i delimiter >
_return       <- < 'return'i delimiter >
_rol          <- < 'rol'i delimiter >
_ror          <- < 'ror'i delimiter >
_select       <- < 'select'i delimiter >
_severity     <- < 'severity'i delimiter >
_signal       <- < 'signal'i delimiter >
_shared       <- < 'shared'i delimiter >
_sla          <- < 'sla'i delimiter >
_sll          <- < 'sll'i delimiter >
_sra          <- < 'sra'i delimiter >
_srl          <- < 'srl'i delimiter >
_subtype      <- < 'subtype'i delimiter >
_then         <- < 'then'i delimiter >
_to           <- < 'to'i delimiter >
_transport    <- < 'transport'i delimiter >
_type         <- < 'type'i delimiter >
_unaffected   <- < 'unaffected'i delimiter >
_units        <- < 'units'i delimiter >
_until        <- < 'until'i delimiter >
_use          <- < 'use'i delimiter >
_variable     <- < 'variable'i delimiter >
_wait         <- < 'wait'i delimiter >
_when         <- < 'when'i delimiter >
_while        <- < 'while'i delimiter >
_with         <- < 'with'i delimiter >
_xnor         <- < 'xnor'i delimiter >
_xor          <- < 'xor'i delimiter >

# PSL reserved keywords
# TODO: Unused keywords are commented out
#         Find out what they're for
#_assume       <- 'assume'i delimiter >    # VHDL-2008 only
#_assume_guarantee <- 'assume_guarantee'i delimiter > # VHDL-2008 only
#_cover        <- < 'cover'i delimiter >     # VHDL-2008 only
_default      <- < 'default'i delimiter >   # VHDL-2008 only
#_fairness     <- < 'fairness'i delimiter >  # VHDL-2008 only
_property     <- < 'property'i delimiter >  # VHDL-2008 only
#_restrict     <- 'restrict'i delimiter >      # VHDL-2008 only
#_restrict_guarantee <- 'restrict_guarantee'i delimiter > # VHDL-2008 only
_sequence     <- < 'sequence'i delimiter >  # VHDL-2008 only
#_strong       <- < 'strong'i delimiter >    # VHDL-2008 only
#_vmode        <- < 'vmode'i delimiter >     # VHDL-2008 only
#_vprop        <- < 'vprop'i delimiter >     # VHDL-2008 only
_vunit        <- < 'vunit'i delimiter >     # VHDL-2008 only

keyword <- _abs / _access / _after / _alias / _all / _and / _architecture / _array / _assert / _attribute
/ _begin / _block / _body / _buffer / _bus
/ _case / _component / _configuration / _constant / _context
/ _disconnect / _downto
/ _else / _elsif / _end / _entity / _exit
/ _file / _for / _force / _function
/ _generate / _generic / _group / _guarded
/ _if / _impure / _in / _inertial / _inout / _is
/ _label / _library / _linkage / _literal / _loop
/ _map / _mod
/ _nand / _new / _next / _nor / _not / _null
/ _of / _on / _open / _or / _others / _out
/ _package / _parameter / _port / _postponed / _procedure / _process / _protected / _pure
/ _range / _record / _register / _reject / _release / _rem / _report / _return / _rol / _ror
/ _select / _severity / _signal / _shared / _sla / _sll / _sra / _srl / _subtype
/ _then / _to / _transport / _type
/ _unaffected / _units / _until / _use
/ _variable
/ _wait / _when / _while / _with
/ _xnor / _xor

# ------------------------------------------------------------------------
# Character set : Section 15.2
upper_case_letter <- [A-Z] / [ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞ]
lower_case_letter <- [a-z] / [àáâãäåæçèéêëìíîïðñòóôõöøùúûüýþ]
special_character <- space / quot_d / [#&'()*+,-./:;<=>?@\[\]_`|]
other_special_character <- backslash backslash / [!$%^{}~¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿×÷]
digit <- [0-9]

delimiter <- !( upper_case_letter / lower_case_letter / digit / '_' )

# 'format_effector' is unused because of %whitespace rule.
# format_effector <- space / '\t' / '\r' / '/n'

# ------------------------------------------------------------------------
# Lexical elements, separators, and delimiters : Section 15.3

# Delimiters
colon     <- ":"
semicolon <- ";"
lrpar     <- "("
rrpar     <- ')'
#backtick  <- '`'
quot_s    <- "'"
quot_d    <- '"'
backslash <- "\\"
hash      <- "#"
space     <- " "
dot       <- "."
plus      <- "+"
comma     <- ","
minus     <- "-"
mult      <- "*"
div       <- "/"
equal     <- "="
concat    <- "&"
less_than <- "<"
grtr_than <- ">"
bar       <- "|"

underline <- "_"
space_character <- " "

# Compound delimiters
arrow          <- "=>"
exponential    <- "**"
var_assignment <- ":="
not_equal      <- "/="
assignment     <- "<="
less_or_equal  <- "<="
grtr_or_equal  <- ">="
box            <- "<>"
condition_operator     <- "??"   # VHDL-2008 only
matching_equality      <- "?="   # VHDL-2008 only
matching_inequality    <- "?/="  # VHDL-2008 only
matching_less_than     <- "?<"   # VHDL-2008 only
matching_less_or_equal <- "?<="  # VHDL-2008 only
matching_grtr_than     <- "?>"   # VHDL-2008 only
matching_grtr_or_equal <- "?>="  # VHDL-2008 only
double_less            <- "<<"   # VHDL-2008 only
double_grtr            <- ">>"   # VHDL-2008 only

# ------------------------------------------------------------------------
# Main section of the standard

# Section 8.7
absolute_pathname <- dot partial_pathname

# Section 15.5.1
abstract_literal <- based_literal / decimal_literal

# Section 5.4.1
access_type_definition <- _access subtype_indication

# Section 6.5.7.1
actual_designator <-
( _inertial )? expression
# / signal_name # /signal_/name
# / variable_name # /variable_/name
# / file_name # /file_/name
/ subtype_indication
# / subprogram_name # /subprogram_/name
# / instantiated_package_name # /instantiated_package_/name
/ name
/ _open

# Section 9.3.4
# actual_parameter_part <- /parameter_/association_list
actual_parameter_part <- association_list

# Section 6.5.7.1
actual_part <-
name lrpar actual_designator rrpar
/ type_mark lrpar actual_designator rrpar
/ actual_designator
# / /function_/name lrpar actual_designator rrpar

# Section 9.2
adding_operator <- plus / minus / concat

# Section 9.3.3.1
aggregate <-
lrpar element_association ( comma element_association )* rrpar

# Section 6.6.1
alias_declaration <-
_alias alias_designator ( colon subtype_indication )? _is name ( signature )? semicolon

# Section 6.6.1
alias_designator <- identifier / character_literal / operator_symbol

# Section 9.3.7
allocator <-
_new subtype_indication
/ _new qualified_expression

# Section 3.3.1
architecture_body <-
# _architecture identifier _of /entity_/name _is
_architecture identifier _of name _is
architecture_declarative_part
_begin
architecture_statement_part
#_end ( _architecture )? ( /architecture_/simple_name )? semicolon
_end ( _architecture )? ( simple_name )? semicolon

# Section 3.3.2
architecture_declarative_part <-
( block_declarative_item )*

# Section 3.3.3
architecture_statement_part <-
( concurrent_statement )*

# Section 5.3.2.1
array_constraint <-
index_constraint ( array_element_constraint )?
/ lrpar _open rrpar ( array_element_constraint )?

# Section 5.3.2.1
array_element_constraint <- element_constraint

# Section 6.3
array_element_resolution <- resolution_indication

# Section 5.3.2.1
array_type_definition <- unbounded_array_definition / constrained_array_definition

# Section 10.3
assertion <-
_assert condition
( _report expression )?
( _severity expression )?

# Section 10.3
assertion_statement <- ( label colon )? assertion semicolon

# Section 6.5.7.1
association_element <-
( formal_part arrow )? actual_part

# Section 6.5.7.1
association_list <-
association_element ( comma association_element )*

# Section 6.7
attribute_declaration <-
_attribute identifier colon type_mark semicolon

# Section 8.6
# attribute_designator <- /attribute_/simple_name
# Bypass using 'simple_name' because simple name fails on the 'range' keyword
attribute_designator <- extended_identifier / basic_identifier_or_attribute

# Section 8.6
attribute_name <-
identifier ( signature )? quot_s attribute_designator ( lrpar expression rrpar )?

# Section 7.2
attribute_specification <-
_attribute attribute_designator _of entity_specification _is expression semicolon

# Section 15.5.3
base <- integer

# Section 15.8
base_specifier <- 'B'i / 'O'i / 'X'i / 'UB'i / 'UO'i / 'UX'i / 'SB'i / 'SO'i / 'SX'i / 'D'i

# Section 15.5.3
based_integer <- < extended_digit ( ( underline )? extended_digit )* >

# Section 15.5.3
based_literal <-
base hash based_integer ( dot based_integer )? hash ( exponent )?

# Section 15.2
# TODO: Currently unused - find out what it's for
#basic_character <-
#basic_graphic_character / format_effector

# Section 15.2
basic_graphic_character <-
special_character / upper_case_letter / digit / space_character

# Section 15.4.2
basic_identifier <- !keyword < letter ( ( underline )? letter_or_digit )* >

# Custom basic identifier for attributes
basic_identifier_or_attribute <- < letter ( ( underline )? letter_or_digit )* >

# Section 7.3.2.1
binding_indication <-
( _use entity_aspect )?
( generic_map_aspect )?
( port_map_aspect )?

# Section 15.8
bit_string_literal <- ( integer )? base_specifier quot_d ( bit_value ) quot_d

# Section 15.8
# Deviate from the spec because bit strings don't have the more unusual characters that are in a graphic_character
# Technically, it should just be '0-9a-fA-FuUxXzZwWlLhH-', but that's a handful...
#bit_value <- graphic_character ( ( underline )? graphic_character )*
bit_value <- ( [0-9a-zA-Z] / minus ) ( ( underline )? ( [0-9a-zA-Z] / minus ) )*

# Section 3.4.2
block_configuration <-
_for block_specification
( use_clause )*
( configuration_item )*
_end _for semicolon

# Section 3.3.2
block_declarative_item <- subprogram_declaration
/ subprogram_body
/ subprogram_instantiation_declaration
/ package_declaration
/ package_body
/ package_instantiation_declaration
/ type_declaration
/ subtype_declaration
/ constant_declaration
/ signal_declaration
# / /shared_/variable_declaration
/ variable_declaration
/ file_declaration
/ alias_declaration
/ component_declaration
/ attribute_declaration
/ attribute_specification
/ configuration_specification
/ disconnection_specification
/ use_clause
/ group_template_declaration
/ group_declaration
# / PSL_Property_Declaration # TODO
# / PSL_Sequence_Declaration # TODO
# / PSL_Clock_Declaration    # TODO

# Section 11.2
block_declarative_part <-
( block_declarative_item )*

# Section 11.2
block_header <-
( generic_clause
( generic_map_aspect semicolon )? )?
( port_clause
( port_map_aspect semicolon )? )?
( port_clause
( port_map_aspect semicolon )? )?

# Section 3.4.2
block_specification <-
# /architecture_/name
name
# / /block_statement_/label
/ label
#/ generate_statement_label ( lrpar generate_specification rrpar )?
/ label ( lrpar generate_specification rrpar )?

# Section 11.2
block_statement <-
# /block_/label colon
label colon
# _block ( lrpar /guard_/condition rrpar )? ( _is )?
_block ( lrpar condition rrpar )? ( _is )?
block_header
block_declarative_part
_begin
block_statement_part
#_end _block ( /block_/label )? semicolon
_end _block ( label )? semicolon

# Section 11.2
block_statement_part <-
( concurrent_statement )*

# Section 11.8
case_generate_alternative <-
# _when ( /alternative_/label colon )? choices arrow
_when ( label colon )? choices arrow
generate_statement_body

# Section 11.8
case_generate_statement <-
# /generate_/label colon
label colon
_case expression _generate
case_generate_alternative
( case_generate_alternative )*
# _end _generate ( /generate_/label )? semicolon
_end _generate ( label )? semicolon

# Section 10.9
case_statement <-
# ( /case_/label colon )?
( label colon )?
_case ( '?' )? expression _is
case_statement_alternative
( case_statement_alternative )*
# _end _case ( '?' )? ( /case_/label )? semicolon
_end _case ( '?' )? ( label )? semicolon

# Section 10.9
case_statement_alternative <-
_when choices arrow
sequence_of_statements

# Section 15.6
# PEG parser notes: need to locally disable whitespace using the '< >' tokenisers
# https://github.com/yhirose/cpp-peglib/issues/44
character_literal <- < "'" < graphic_character / backslash > "'" >

# Section 9.3.3.1
choice <-
_others
/ simple_expression
# / /discrete_/range
# / /element_/simple_name
/ range
/ simple_name

# Section 9.3.3.1
choices <- choice ( bar choice )*

# Section 3.4.3
component_configuration <-
_for component_specification
( binding_indication semicolon )?
( verification_unit_binding_indication semicolon )*
( block_configuration )?
_end _for semicolon

# Section 6.8
component_declaration <-
_component identifier ( _is )?
# ( /local_/generic_clause )?
( generic_clause )?
# ( /local_/port_clause )?
( port_clause )?
# _end _component ( /component_/simple_name )? semicolon
_end _component ( simple_name )? semicolon

# Section 11.7.1
component_instantiation_statement <-
# /instantiation_/label colon instantiated_unit
label colon instantiated_unit
( generic_map_aspect )?
( port_map_aspect )? semicolon

# Section 7.3.1
# component_specification <- instantiation_list colon /component_/name
component_specification <- instantiation_list colon name

# Section 5.3.1
composite_type_definition <- array_type_definition
/ record_type_definition

# Section 7.3.1
compound_configuration_specification <-
_for component_specification binding_indication semicolon
verification_unit_binding_indication semicolon
( verification_unit_binding_indication semicolon )*
_end _for semicolon

# Section 11.5
concurrent_assertion_statement <-
( label colon )? ( _postponed )? assertion semicolon

# Section 11.6
concurrent_conditional_signal_assignment <-
target assignment ( _guarded )? ( delay_mechanism )? conditional_waveforms semicolon

# Section 11.4
concurrent_procedure_call_statement <-
( label colon )? ( _postponed )? procedure_call semicolon

# Section 11.6
concurrent_selected_signal_assignment <-
_with expression _select ( '?' )?
target assignment ( _guarded )? ( delay_mechanism )? selected_waveforms semicolon

# Section 11.6
concurrent_signal_assignment_statement <-
( label colon )? ( _postponed )? concurrent_simple_signal_assignment
/ ( label colon )? ( _postponed )? concurrent_conditional_signal_assignment
/ ( label colon )? ( _postponed )? concurrent_selected_signal_assignment

# Section 11.6
concurrent_simple_signal_assignment <-
target assignment ( _guarded )? ( delay_mechanism )? waveform semicolon

# Section 11.1
concurrent_statement <-
block_statement
/ process_statement
/ concurrent_procedure_call_statement
/ concurrent_assertion_statement
/ concurrent_signal_assignment_statement
/ component_instantiation_statement
/ generate_statement
# / PSL_PSL_Directive # TODO

# Section 10.2
condition <- expression

# Section 10.2
condition_clause <- _until condition

# Section 9.2.1
# condition_operator   <-   ?? # Defined above, in the top section

# Section 10.5.3
conditional_expressions <-
expression _when condition
( _else expression _when condition )*
( _else expression )?

# Section 10.5.3
conditional_force_assignment <-
target assignment _force ( force_mode )? conditional_expressions semicolon

# Section 10.5.3
conditional_signal_assignment <-
conditional_waveform_assignment
/ conditional_force_assignment

# Section 10.6.3
conditional_variable_assignment <-
target var_assignment conditional_expressions semicolon

# Section 10.5.3
conditional_waveform_assignment <-
target assignment ( delay_mechanism )? conditional_waveforms semicolon

# Section 10.5.3
conditional_waveforms <-
waveform _when condition
( _else waveform _when condition )*
( _else waveform )?

# Section 3.4.1
configuration_declaration <-
# _configuration identifier _of /entity_/name _is
_configuration identifier _of name _is
configuration_declarative_part
( verification_unit_binding_indication semicolon )*
block_configuration
# _end ( _configuration )? ( /configuration_/simple_name )? semicolon
_end ( _configuration )? ( simple_name )? semicolon

# Section 3.4.1
configuration_declarative_item <-
use_clause
/ attribute_specification
/ group_declaration

# Section 3.4.1
configuration_declarative_part <-
( configuration_declarative_item )*

# Section 3.4.2
configuration_item <- block_configuration
/ component_configuration

# Section 7.3.1
configuration_specification <-
simple_configuration_specification
/ compound_configuration_specification

# Section 6.4.2.2
constant_declaration <-
_constant identifier_list colon subtype_indication ( var_assignment expression )? semicolon

# Section 5.3.2.1
constrained_array_definition <-
# _array index_constraint _of /element_/subtype_indication
_array index_constraint _of subtype_indication

# Section 6.3
constraint <-
range_constraint
/ array_constraint
/ record_constraint

# Section 13.4
context_clause <- ( context_item )*

# Section 13.3
context_declaration <-
_context identifier _is
context_clause
# _end ( _context )? ( /context_/simple_name )? semicolon
_end ( _context )? ( simple_name )? semicolon

# Section 13.4
context_item <-
library_clause
/ use_clause
/ context_reference

# Section 13.4
context_reference <-
_context selected_name ( comma selected_name )* semicolon

# Section 15.5.2
decimal_literal <- integer ( dot integer )? ( exponent )?

# Section 10.5.2.1
delay_mechanism <-
_transport
# / ( _reject /time_/expression )? _inertial
/ ( _reject expression )? _inertial

# Section 13.1
design_file <- design_unit ( design_unit )*

# Section 13.1
design_unit <- context_clause library_unit

# Section 4.2.1
designator <- identifier / operator_symbol

# Section 5.2.1
direction <- _to / _downto

# Section 7.4
disconnection_specification <-
# _disconnect guarded_signal_specification _after /time_/expression semicolon
_disconnect guarded_signal_specification _after expression semicolon

# Section 5.3.2.1
# discrete_range <- /discrete_/subtype_indication / range
discrete_range <-
range
/ subtype_indication

# Section 9.3.3.1
element_association <-
( choices arrow )? expression

# Section 6.3
element_constraint <-
array_constraint
/ record_constraint

# Section 5.3.3
element_declaration <-
identifier_list colon element_subtype_definition semicolon

# Section 6.3
element_resolution <- array_element_resolution / record_resolution

# Section 5.3.3
element_subtype_definition <- subtype_indication

# Section 7.3.2.2
entity_aspect <-
# _entity /entity_/name ( lrpar /architecture_/identifier rrpar )?
_entity name ( lrpar identifier rrpar )?
# / _configuration /configuration_/name
/ _configuration name
/ _open

# Section 7.2
entity_class <-
_entity
/ _architecture
/ _configuration
/ _procedure
/ _function
/ _package
/ _type
/ _subtype
/ _constant
/ _signal
/ _variable
/ _component
/ _label
/ _literal
/ _units
/ _group
/ _file
/ _property
/ _sequence

# Section 6.9
entity_class_entry <- entity_class ( box )?

# Section 6.9
entity_class_entry_list <-
entity_class_entry ( comma entity_class_entry )*

# Section 3.2.1
entity_declaration <-
_entity identifier _is
entity_header
entity_declarative_part
( _begin
entity_statement_part )?
# _end ( _entity )? ( /entity_/simple_name )? semicolon
_end ( _entity )? ( simple_name )? semicolon

# Section 3.2.3
entity_declarative_item <- subprogram_declaration
/ subprogram_body
/ subprogram_instantiation_declaration
/ package_declaration
/ package_body
/ package_instantiation_declaration
/ type_declaration
/ subtype_declaration
/ constant_declaration
/ signal_declaration
# / /shared_/variable_declaration
/ variable_declaration
/ file_declaration
/ alias_declaration
/ attribute_declaration
/ attribute_specification
/ disconnection_specification
/ use_clause
/ group_template_declaration
/ group_declaration
# / PSL_Property_Declaration # TODO
# / PSL_Sequence_Declaration # TODO
# / PSL_Clock_Declaration # TODO

# Section 3.2.3
entity_declarative_part <-
( entity_declarative_item )*

# Section 7.2
entity_designator <- entity_tag ( signature )?

# Section 3.2.3
entity_header <-
# ( /formal_/generic_clause )?
( generic_clause )?
# ( /formal_/port_clause )?
( port_clause )?

# Section 7.2
entity_name_list <-
_others
/ _all
/ entity_designator ( comma entity_designator )*

# Section 7.2
entity_specification <-
entity_name_list colon entity_class

# Section 3.2.4
entity_statement <-
concurrent_assertion_statement
# / /passive_/concurrent_procedure_call_statement
/ concurrent_procedure_call_statement
# / /passive_/process_statement
/ process_statement
# / PSL_PSL_Directive # TODO

# Section 3.2.4
entity_statement_part <-
( entity_statement )*

# Section 7.2
entity_tag <- simple_name / character_literal / operator_symbol

# Section 5.2.2.1
enumeration_literal <- identifier / character_literal

# Section 5.2.2.1
enumeration_type_definition <-
lrpar enumeration_literal ( comma enumeration_literal )* rrpar

# Section 10.2
exit_statement <-
# ( label colon )? _exit ( /loop_/label )? ( _when condition )? semicolon
( label colon )? _exit ( label )? ( _when condition )? semicolon

# Section 15.5.2
exponent <- "E" ( plus )? integer / "E" minus integer

# Section 9.1
expression <-
logical_expression
/ condition_operator primary

# Section 15.5.3
extended_digit <- digit / letter

# Section 15.4.3
extended_identifier <- < backslash graphic_character ( graphic_character )* backslash >

# Section 8.7
external_name <-
external_constant_name
/ external_signal_name
/ external_variable_name

# Section 8.7
external_constant_name <-
double_less _constant external_pathname colon subtype_indication double_grtr

# Section 8.7
external_signal_name <-
double_less _signal external_pathname colon subtype_indication double_grtr

# Section 8.7
external_variable_name <-
double_less _variable external_pathname colon subtype_indication double_grtr

# Section 8.7
external_pathname <-
package_pathname
/ absolute_pathname
/ relative_pathname

# Section 9.1
factor <-
_abs primary
/ _not primary
/ primary ( exponential primary )?
/ logical_operator primary

# Section 6.4.2.5
file_declaration <-
_file identifier_list colon subtype_indication ( file_open_information )? semicolon

# Section 6.4.2.5
# file_logical_name <- /string_/expression
file_logical_name <- expression

# Section 6.4.2.5
file_open_information <-
# ( _open /file_open_kind_/expression )? _is file_logical_name
( _open expression )? _is file_logical_name

# Section 5.5.1
file_type_definition <-
_file _of type_mark

# Section 5.2.5.1
floating_type_definition <- range_constraint

# Section 11.8
for_generate_statement <-
# /generate_/label colon
# _for /generate_/parameter_specification _generate
# /generate_/statement_body
# _end _generate ( /generate_/label )? semicolon
label colon
_for parameter_specification _generate
generate_statement_body
_end _generate ( label )? semicolon

# Section 10.5.2.1
force_mode <- _in / _out

# Section 6.5.7.1
formal_designator <-
# /generic_/name
# / /port_/name
# / /parameter_/name
name

# Section 4.2.2.1
# formal_parameter_list <- /parameter_/interface_list
formal_parameter_list <- interface_list

# Section 6.5.7.1
formal_part <-
# / /function_/name lrpar formal_designator rrpar
name lrpar formal_designator rrpar
/ type_mark lrpar formal_designator rrpar
/ formal_designator

# Section 6.2
full_type_declaration <-
_type identifier _is type_definition semicolon

# Section 9.3.4
function_call <-
# /function_/name ( lrpar actual_parameter_part rrpar )?
identifier lrpar ( actual_parameter_part )? rrpar

# Section 4.2.1
function_specification <-
( _pure / _impure )? _function designator
subprogram_header
( ( _parameter )? lrpar formal_parameter_list rrpar )? _return type_mark

# Section 3.4.2
generate_specification <-
# /static_/discrete_range
# / /static_/expression
# / /alternative_/label
discrete_range
/ expression
/ label

# Section 11.8
generate_statement <-
for_generate_statement
/ if_generate_statement
/ case_generate_statement

# Section 11.8
generate_statement_body <-
( block_declarative_part
_begin )?
( concurrent_statement )*
# ( _end ( /alternative_/label )? semicolon )?
( _end ( label )? semicolon )?

# Section 6.5.6.2
generic_clause <-
_generic lrpar generic_list rrpar semicolon

# Section 6.5.6.2
# generic_list <- /generic_/interface_list
generic_list <- interface_list

# Section 6.5.6.2
generic_map_aspect <-
# _generic _map lrpar /generic_/association_list rrpar
_generic _map lrpar association_list rrpar

# Section 15.2
graphic_character <-
basic_graphic_character / lower_case_letter / other_special_character

# Section 6.10
group_constituent <- name / character_literal

# Section 6.10
group_constituent_list <- group_constituent ( comma group_constituent )*

# Section 6.10
group_declaration <-
# _group identifier colon /group_template_/name lrpar group_constituent_list rrpar semicolon
_group identifier colon name lrpar group_constituent_list rrpar semicolon

# Section 6.9
group_template_declaration <-
_group identifier _is lrpar entity_class_entry_list rrpar semicolon

# Section 7.4
guarded_signal_specification <-
# /guarded_/signal_list colon type_mark
signal_list colon type_mark

# Section 15.4.1
identifier <- extended_identifier / basic_identifier

# Section 5.3.3
identifier_list <- identifier ( comma identifier )*

# Section 11.8
# if_generate_statement <-
# /generate_/label colon
# _if ( /alternative_/label colon )? condition _generate
# generate_statement_body
# ( _elsif ( /alternative_/label colon )? condition _generate
# generate_statement_body )*
# ( _else ( /alternative_/label colon )? _generate
# generate_statement_body )?
# _end _generate ( /generate_/label )? semicolon
if_generate_statement <-
label colon
_if ( label colon )? condition _generate
generate_statement_body
( _elsif ( label colon )? condition _generate
generate_statement_body )*
( _else ( label colon )? _generate
generate_statement_body )?
_end _generate ( label )? semicolon

# Section 10.8
if_statement <-
# ( /if_/label colon )?
( label colon )?
_if condition _then
sequence_of_statements
( _elsif condition _then
sequence_of_statements )*
( _else sequence_of_statements )?
# _end _if ( /if_/label )? semicolon
_end _if ( label )? semicolon

# Section 5.4.2
incomplete_type_declaration <- _type identifier semicolon

# Section 5.3.2.1
index_constraint <- lrpar discrete_range ( comma discrete_range )* rrpar

# Section 5.3.2.1
index_subtype_definition <- type_mark _range box

# Section 8.4
# Currently unused due to changes to 'name' rule
#indexed_name <- identifier lrpar expression ( comma expression )* rrpar

# Section 11.7.1
instantiated_unit <-
# ( _component )? /component_/name
# / _entity /entity_/name ( lrpar /architecture_/identifier rrpar )?
# / _configuration /configuration_/name
_entity name ( lrpar identifier rrpar )?
/ _configuration name
/ ( _component )? name

# Section 7.3.1
instantiation_list <-
# /instantiation_/label ( comma /instantiation_/label )*
_others
/ _all
/ label ( comma label )*

# Section 15.5.2
integer <- < digit ( ( underline )? digit )* >

# Section 5.2.3.1
integer_type_definition <- range_constraint

# Section 6.5.2
interface_constant_declaration <-
# ( _constant )? identifier_list colon ( _in )? subtype_indication ( var_assignment /static_/expression )?
( _constant )? identifier_list colon ( _in )? subtype_indication ( var_assignment expression )?

# Section 6.5.1
interface_declaration <- interface_object_declaration
/ interface_type_declaration
/ interface_subprogram_declaration
/ interface_package_declaration

# Section 6.5.6.1
interface_element <- interface_declaration

# Section 6.5.2
interface_file_declaration <-
_file identifier_list colon subtype_indication

# Section 6.5.4
interface_function_specification <-
( _pure / _impure )? _function designator
( ( _parameter )? lrpar formal_parameter_list rrpar )? _return type_mark

# Section 6.5.3
interface_incomplete_type_declaration <- _type identifier

# Section 6.5.6.1
interface_list <-
interface_element ( semicolon interface_element )*

# Section 6.5.2
interface_object_declaration <-
interface_signal_declaration
/ interface_constant_declaration
/ interface_variable_declaration
/ interface_file_declaration

# Section 6.5.5
interface_package_declaration <-
_package identifier _is
# _new /uninstantiated_package_/name interface_package_generic_map_aspect
_new name interface_package_generic_map_aspect

# Section 6.5.5
interface_package_generic_map_aspect <-
generic_map_aspect
/ _generic _map lrpar box rrpar
/ _generic _map lrpar _default rrpar

# Section 6.5.4
interface_procedure_specification <-
_procedure designator
( ( _parameter )? lrpar formal_parameter_list rrpar )?

# Section 6.5.2
interface_signal_declaration <-
# ( _signal )? identifier_list colon ( mode )? subtype_indication ( _bus )? ( var_assignment /static_/expression )?
( _signal )? identifier_list colon ( mode )? subtype_indication ( _bus )? ( var_assignment expression )?

# Section 6.5.4
interface_subprogram_declaration <-
interface_subprogram_specification ( _is interface_subprogram_default )?

# Section 6.5.4
# interface_subprogram_default <- /subprogram_/name / box
interface_subprogram_default <- name / box

# Section 6.5.4
interface_subprogram_specification <-
interface_procedure_specification / interface_function_specification

# Section 6.5.3
interface_type_declaration <- interface_incomplete_type_declaration

# Section 6.5.2
interface_variable_declaration <-
# ( _variable )? identifier_list colon ( mode )? subtype_indication ( var_assignment /static_/expression )?
( _variable )? identifier_list colon ( mode )? subtype_indication ( var_assignment expression )?

# Section 10.10
iteration_scheme <-
_while condition
# / _for /loop_/parameter_specification
/ _for parameter_specification

# Section 11.8
label <- identifier

# Section 15.4.2
letter <- upper_case_letter / lower_case_letter

# Section 15.4.2
letter_or_digit <- letter / digit

# Section 13.2
library_clause <- _library logical_name_list semicolon

# Section 13.1
library_unit <-
primary_unit
/ secondary_unit

# Section 9.3.2
literal <-
string_literal
/ bit_string_literal
/ enumeration_literal
/ numeric_literal
/ _null

# Section 9.1
logical_expression <-
relation ( logical_operator relation )*

# Section 13.2
logical_name <- identifier

# Section 13.2
logical_name_list <- logical_name ( comma logical_name )*

# Section 9.2.1
logical_operator <- _and / _or / _nand / _nor / _xor / _xnor

# Section 10.10
loop_statement <-
# ( /loop_/label colon )?
( label colon )?
( iteration_scheme )? _loop
sequence_of_statements
# _end _loop ( /loop_/label )? semicolon
_end _loop ( label )? semicolon

# Section 9.2.1
# TODO: Currently unused - find out what it's for
#miscellaneous_operator <- exponential / _abs / _not

# Section 6.5.2
mode <- _inout / _in / _out / _inout / _buffer / _linkage

# Section 9.2.1
multiplying_operator <- mult / div / _mod / _rem

# Section 8.1
#name <-
#simple_name
#/ operator_symbol
#/ character_literal
#/ selected_name
#/ indexed_name
#/ slice_name
#/ attribute_name
#/ external_name

# 'name' is left-recursive because the following use "prefix", which uses 'name'
# - selected_name
# - indexed_name
# - slice_name
# - attribute_name
# Break the left-recusrion by re-defining these

name <-
!keyword name_prefix ( name_part )*
/ external_name

name_prefix <- identifier / string_literal

name_part <-
function_call_part
/ selected_name_part
/ indexed_name_part
/ slice_name_part
/ attribute_name_part

selected_name_part <- ( dot suffix )+

function_call_part <- lrpar function_call_element ( comma name )* rrpar
function_call_element <- attribute_name / simple_expression

indexed_name_part <- lrpar expression ( comma expression )* rrpar

slice_name_part <- lrpar discrete_range rrpar / range

attribute_name_part <-
( signature )? quot_s attribute_designator ( lrpar expression rrpar )?

# Section 10.11
next_statement <-
# ( label colon )? _next ( /loop_/label )? ( _when condition )? semicolon
( label colon )? _next ( label )? ( _when condition )? semicolon

# Section 10.14
null_statement <- ( label colon )? _null semicolon

# Section 9.3.2
numeric_literal <-
physical_literal
/ abstract_literal

# Section 6.4.2.1
# TODO: Not used - see what it's used for
#object_declaration <-
#constant_declaration
#/ signal_declaration
#/ variable_declaration
#/ file_declaration

# Section 4.2.1
operator_symbol <- string_literal

# Section 4.8
package_body <-
# _package _body /package_/simple_name _is
# package_body_declarative_part
# _end ( _package _body )? ( /package_/simple_name )? semicolon
_package _body simple_name _is
package_body_declarative_part
_end ( _package _body )? ( simple_name )? semicolon

# Section 4.8
package_body_declarative_item <-
subprogram_declaration
/ subprogram_body
/ subprogram_instantiation_declaration
/ package_declaration
/ package_body
/ package_instantiation_declaration
/ type_declaration
/ subtype_declaration
/ constant_declaration
/ variable_declaration
/ file_declaration
/ alias_declaration
/ attribute_declaration
/ attribute_specification
/ use_clause
/ group_template_declaration
/ group_declaration

# Section 4.8
package_body_declarative_part <-
( package_body_declarative_item )*

# Section 4.7
package_declaration <-
_package identifier _is
package_header package_declarative_part
# _end ( _package )? ( /package_/simple_name )? semicolon
_end ( _package )? ( simple_name )? semicolon

# Section 4.7
package_declarative_item <-
subprogram_declaration
/ subprogram_instantiation_declaration
/ package_declaration
/ package_instantiation_declaration
/ type_declaration
/ subtype_declaration
/ constant_declaration
/ signal_declaration
/ variable_declaration
/ file_declaration
/ alias_declaration
/ component_declaration
/ attribute_declaration
/ attribute_specification
/ disconnection_specification
/ use_clause
/ group_template_declaration
/ group_declaration
# / PSL_Property_Declaration # TODO
# / PSL_Sequence_Declaration # TODO

# Section 4.7
package_declarative_part <-
( package_declarative_item )*

# Section 4.7
package_header <-
( generic_clause
( generic_map_aspect semicolon )? )?

# Section 4.9
package_instantiation_declaration <-
# _package identifier _is _new /uninstantiated_package_/name
_package identifier _is _new name
( generic_map_aspect )? semicolon

# Section 8.7
package_pathname <-
# '@' /library_/logical_name dot ( /package_/simple_name dot )* /object_/simple_name
'@' logical_name dot ( simple_name dot )* simple_name

# Section 10.10
parameter_specification <-
identifier _in discrete_range

# Section 8.7
# partial_pathname <- ( pathname_element dot )* /object_/simple_name
partial_pathname <- ( pathname_element dot )* simple_name

# Section 8.7
pathname_element <-
# /entity_/simple_name
# / /component_instantiation_/label
# / /block_/label
# / /generate_statement_/label ( lrpar /static_/expression rrpar )?
# / /package_/simple_name
simple_name
/ label
/ label ( lrpar expression rrpar )?

# Section 5.2.4.1
# physical_literal <- ( abstract_literal )? /unit_/name
physical_literal <- ( abstract_literal )? name

# Section 5.2.4.1
physical_type_definition <-
range_constraint
_units
primary_unit_declaration
( secondary_unit_declaration )*
# _end _units ( /physical_type_/simple_name )?
_end _units ( simple_name )?

# Section 6.5.6.3
port_clause <-
_port lrpar port_list rrpar semicolon

# Section 6.5.6.3
# port_list <- /port_/interface_list
port_list <- interface_list

# Section 6.5.7.3
port_map_aspect <-
# _port _map lrpar /port_/association_list rrpar
_port _map lrpar association_list rrpar

# Section 8.1
# Note: 'prefix' causes left-recursion in the 'name' rule, so
#         it has been replaced with 'identifier'.
#       This may need to be revisited if 'function_call' is needed.
#prefix <-
#name
#/ function_call

# Section 9.1
primary <-
attribute_name
/ qualified_expression
/ name !quot_d
/ function_call
/ aggregate
/ type_conversion
/ allocator
/ lrpar expression rrpar
/ literal

# Section 13.1
primary_unit <-
entity_declaration
/ configuration_declaration
/ package_declaration
/ package_instantiation_declaration
/ context_declaration
# / PSL_Verification_Unit # TODO

# Section 5.2.4.1
primary_unit_declaration <- identifier semicolon

# Section 10.7
# procedure_call <- /procedure_/name ( lrpar actual_parameter_part rrpar )?
procedure_call <- name ( lrpar actual_parameter_part rrpar )?

# Section 10.7
procedure_call_statement <- ( label colon )? procedure_call semicolon

# Section 4.2.1
procedure_specification <-
_procedure designator subprogram_header
( ( _parameter )? lrpar formal_parameter_list rrpar )?

# Section 11.3
process_declarative_item <-
subprogram_declaration
/ subprogram_body
/ subprogram_instantiation_declaration
/ package_declaration
/ package_body
/ package_instantiation_declaration
/ type_declaration
/ subtype_declaration
/ constant_declaration
/ variable_declaration
/ file_declaration
/ alias_declaration
/ attribute_declaration
/ attribute_specification
/ use_clause
/ group_template_declaration
/ group_declaration

# Section 11.3
process_declarative_part <-
( process_declarative_item )*

# Section 11.3
process_sensitivity_list <- _all / sensitivity_list

# Section 11.3
process_statement <-
# ( /process_/label colon )?
( label colon )?
( _postponed )? _process ( lrpar process_sensitivity_list rrpar )? ( _is )?
process_declarative_part
_begin
process_statement_part
# _end ( _postponed )? _process ( /process_/label )? semicolon
_end ( _postponed )? _process ( label )? semicolon

# Section 11.3
process_statement_part <-
( sequential_statement )*

# Section 5.6.3
protected_type_body <-
_protected _body
protected_type_body_declarative_part
# _end _protected _body ( /protected_type_/simple_name )?
_end _protected _body ( simple_name )?

# Section 5.6.3
protected_type_body_declarative_item <-
subprogram_declaration
/ subprogram_body
/ subprogram_instantiation_declaration
/ package_declaration
/ package_body
/ package_instantiation_declaration
/ type_declaration
/ subtype_declaration
/ constant_declaration
/ variable_declaration
/ file_declaration
/ alias_declaration
/ attribute_declaration
/ attribute_specification
/ use_clause
/ group_template_declaration
/ group_declaration

# Section 5.6.3
protected_type_body_declarative_part <-
( protected_type_body_declarative_item )*

# Section 5.6.2
protected_type_declaration <-
_protected
protected_type_declarative_part
# _end _protected ( /protected_type_/simple_name )?
_end _protected ( simple_name )?

# Section 5.6.2
protected_type_declarative_item <-
subprogram_declaration
/ subprogram_instantiation_declaration
/ attribute_specification
/ use_clause

# Section 5.6.2
protected_type_declarative_part <-
( protected_type_declarative_item )*

# Section 5.6.1
protected_type_definition <-
protected_type_declaration
/ protected_type_body

# Section 9.3.5
qualified_expression <-
type_mark quot_s lrpar expression rrpar
/ type_mark quot_s aggregate

# Section 5.2.1
range <-
# /range_/attribute_name
simple_expression ( direction simple_expression )?
/ attribute_name

# Section 5.2.1
range_constraint <- _range range

# Section 5.3.3
record_constraint <-
lrpar record_element_constraint ( comma record_element_constraint )* rrpar

# Section 5.3.3
# record_element_constraint <- /record_element_/simple_name element_constraint
record_element_constraint <- simple_name element_constraint

# Section 6.3
# record_element_resolution <- /record_element_/simple_name resolution_indication
record_element_resolution <- simple_name resolution_indication

# Section 6.3
record_resolution <- record_element_resolution ( comma record_element_resolution )*

# Section 5.3.3
record_type_definition <-
_record
element_declaration
( element_declaration )*
# _end _record ( /record_type_/simple_name )?
_end _record ( simple_name )?

# Section 9.1
relation <- shift_expression ( relational_operator shift_expression )?

# Section 9.2.1
matching_operator <- matching_equality / matching_inequality / matching_less_than / matching_less_or_equal / matching_grtr_than / matching_grtr_or_equal
relational_operator <- not_equal / less_or_equal / less_than / grtr_or_equal / grtr_than / matching_operator / equal

# Section 8.7
relative_pathname <- ( '^' dot )* partial_pathname

# Section 10.4
report_statement <-
( label colon )?
_report expression
( _severity expression )? semicolon

# Section 6.3
# resolution_indication <- /resolution_function_/name / lrpar element_resolution rrpar
resolution_indication <- name / lrpar element_resolution rrpar

# Section 10.13
return_statement <-
( label colon )? _return ( expression )? semicolon

# Section 5.2.1
scalar_type_definition <-
physical_type_definition
/ enumeration_type_definition
/ integer_type_definition
/ floating_type_definition

# Section 13.1
secondary_unit <-
architecture_body
/ package_body

# Section 5.2.4.1
secondary_unit_declaration <- identifier equal physical_literal semicolon

# Section 10.5.4
selected_expressions <-
( expression _when choices comma )*
expression _when choices

# Section 10.5.4
selected_force_assignment <-
_with expression _select ( '?' )?
target assignment _force ( force_mode )? selected_expressions semicolon

# Section 8.3
selected_name <- identifier ( dot suffix )*

# Section 10.5.4
selected_signal_assignment <-
selected_waveform_assignment / selected_force_assignment

# Section 10.6.4
selected_variable_assignment <-
_with expression _select ( '?' )?
target var_assignment selected_expressions semicolon

# Section 10.5.4
selected_waveform_assignment <-
_with expression _select ( '?' )?
target assignment ( delay_mechanism )? selected_waveforms semicolon

# Section 10.5.4
selected_waveforms <-
( waveform _when choices comma )*
waveform _when choices

# Section 10.2
sensitivity_clause <- _on sensitivity_list

# Section 10.2
# sensitivity_list <- /signal_/name ( comma /signal_/name )*
sensitivity_list <- name ( comma name )*

# Section 10.1
sequence_of_statements <-
( sequential_statement )*

# Section 10.1
sequential_statement <-
wait_statement
/ assertion_statement
/ report_statement
/ signal_assignment_statement
/ variable_assignment_statement
/ procedure_call_statement
/ if_statement
/ case_statement
/ loop_statement
/ next_statement
/ exit_statement
/ return_statement
/ null_statement

# Section 9.1
shift_expression <-
simple_expression ( shift_operator simple_expression )?

# Section 9.2.1
shift_operator <- _sll / _srl / _sla / _sra / _rol / _ror

# Section 9.2.1
sign <- plus / minus

# Section 10.5.1
signal_assignment_statement <-
( label colon )? simple_signal_assignment
/ ( label colon )? conditional_signal_assignment
/ ( label colon )? selected_signal_assignment

# Section 6.4.2.3
signal_declaration <-
_signal identifier_list colon subtype_indication ( signal_kind )? ( var_assignment expression )? semicolon

# Section 6.4.2.3
signal_kind <- _register / _bus

# Section 7.4
signal_list <-
# /signal_/name ( comma /signal_/name )*
_others
/ _all
/ name ( comma name )*

# Section 4.5.3
signature <- ( ( type_mark ( comma type_mark )* )? ( _return type_mark )? )?

# Section 7.3.1
simple_configuration_specification <-
_for component_specification binding_indication semicolon
( _end _for semicolon )?

# Section 9.1
simple_expression <-
( sign )? term ( adding_operator term )*

# Section 10.5.2.1
simple_force_assignment <-
target assignment _force ( force_mode )? expression semicolon

# Section 8.2
simple_name <- identifier

# Section 10.5.2.1
simple_release_assignment <-
target assignment _release ( force_mode )? semicolon

# Section 10.5.2.1
simple_signal_assignment <-
simple_waveform_assignment
/ simple_force_assignment
/ simple_release_assignment

# Section 10.5.2.1
simple_waveform_assignment <-
target assignment ( delay_mechanism )? waveform semicolon

# Section 10.6.2.1
simple_variable_assignment <-
target var_assignment expression semicolon

# Section 8.5
# Currently unused due to changes to 'name' rule
#slice_name <- identifier lrpar discrete_range rrpar

# Section 15.7
#string_literal <- quot_d ( quot_d quot_d / graphic_character )* quot_d
string_literal <-  < ["] < (quot_d quot_d / !["] .)* > ["] >

# Section 4.3
subprogram_body <-
subprogram_specification _is
subprogram_declarative_part
_begin
subprogram_statement_part
_end ( subprogram_kind )? ( designator )? semicolon

# Section 4.2.1
subprogram_declaration <-
subprogram_specification semicolon

# Section 4.3
subprogram_declarative_item <-
subprogram_declaration
/ subprogram_body
/ subprogram_instantiation_declaration
/ package_declaration
/ package_body
/ package_instantiation_declaration
/ type_declaration
/ subtype_declaration
/ constant_declaration
/ variable_declaration
/ file_declaration
/ alias_declaration
/ attribute_declaration
/ attribute_specification
/ use_clause
/ group_template_declaration
/ group_declaration

# Section 4.3
subprogram_declarative_part <-
( subprogram_declarative_item )*

# Section 4.2.1
subprogram_header <-
( _generic lrpar generic_list rrpar
( generic_map_aspect )? )?

# Section 4.4
subprogram_instantiation_declaration <-
# subprogram_kind identifier _is _new /uninstantiated_subprogram_/name ( signature )?
subprogram_kind identifier _is _new name ( signature )?
( generic_map_aspect )? semicolon

# Section 4.3
subprogram_kind <- _procedure / _function

# Section 4.2.1
subprogram_specification <-
procedure_specification / function_specification

# Section 4.3
subprogram_statement_part <-
( sequential_statement )*

# Section 6.3
subtype_declaration <-
_subtype identifier _is subtype_indication semicolon

# Section 6.3
subtype_indication <-
# ( resolution_indication type_mark / type_mark ) ( constraint )?
name + ( constraint )?

# Section 8.3
suffix <-
simple_name
/ character_literal
/ operator_symbol
/ _all

# Section 10.5.2.1
target <-
name
/ aggregate

# Section 9.1
term <-
factor ( multiplying_operator factor )*

# Section 10.2
# timeout_clause <- _for /time_/expression
timeout_clause <- _for expression

# Section 15.11
# Currently unused: TODO - find where to add this in the grammar
#tool_directive <- backtick identifier ( graphic_character )*

# Section 9.3.6
type_conversion <- type_mark lrpar expression rrpar

# Section 6.2
type_declaration <-
full_type_declaration
/ incomplete_type_declaration

# Section 6.2
type_definition <-
protected_type_definition
/ scalar_type_definition
/ composite_type_definition
/ access_type_definition
/ file_type_definition

# Section 6.3
type_mark <- name
#type_name
#/ subtype_name

# Section 5.3.2.1
unbounded_array_definition <-
_array lrpar index_subtype_definition ( comma index_subtype_definition )* rrpar
# _of /element_/subtype_indication
_of subtype_indication

# Section 12.4
use_clause <-
_use selected_name ( comma selected_name )* semicolon

# Section 10.6.1
variable_assignment_statement <-
( label !var_assignment colon )? simple_variable_assignment
/ ( label !var_assignment colon )? conditional_variable_assignment
/ ( label !var_assignment colon )? selected_variable_assignment

# Section 6.4.2.4
variable_declaration <-
( _shared )? _variable identifier_list colon subtype_indication ( var_assignment expression )? semicolon

# Section 7.3.4
verification_unit_binding_indication <-
_use _vunit verification_unit_list

# Section 7.3.4
# verification_unit_list <- /verification_unit_/name ( comma /verification_unit_/name )*
verification_unit_list <- name ( comma name )*

# Section 10.2
wait_statement <-
( label colon )? _wait ( sensitivity_clause )? ( condition_clause )? ( timeout_clause )? semicolon

# Section 10.5.2.1
waveform <-
waveform_element ( comma waveform_element )*
/ _unaffected

# Section 10.5.2.2
waveform_element <-
# /value_/expression ( _after /time_/expression )?
# / _null ( _after /time_/expression )?
expression ( _after expression )?
/ _null ( _after expression )?

  )");

  vector<char> file_contents;
  if (!read_file(hdl_file_path, file_contents)) {
    cerr << "can't open the file." << endl;
    return -1;
  }

  //  parser.set_verbose_trace(true);

  // Create a way to show error messages
  parser.set_logger([](size_t line, size_t col, const string& msg, const string &rule) {
    cerr << line << ":" << col << ": " << msg <<"\n";
  });

  // Enable packrat parsing for performance; it's too slow otherwise
  parser.enable_packrat_parsing();

  parser.enable_ast();
  std::shared_ptr<peg::Ast> ast;

  // Parse
  parser.parse_n(file_contents.data(), file_contents.size(), ast);

  if (ast) {
    //ast = parser.optimize_ast(ast, false);
    std::cout << peg::ast_to_s(ast);
  }

  return 0;
}
