-------------------------------------------------------------------------------
--
-- IEEE Std 1076-2008 VHDL "Standard" Library in ANSI format
--
-------------------------------------------------------------------------------

package standard is
-- Predefined enumeration types:
  type boolean is (false, true);
  type bit is ('0', '1');
  type character is (
    NUL, SOH, STX, ETX, EOT, ENQ, ACK, BEL,
    BS, HT, LF, VT, FF, CR, SO, SI,
    DLE, DC1, DC2, DC3, DC4, NAK, SYN, ETB,
    CAN, EM, SUB, ESC, FSP, GSP, RSP, USP,
    ' ', '!', '"', '#', '$', '%', '&', ''',
    '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', ':', ';', '<', '=', '>', '?',
    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
    'X', 'Y', 'Z', '[', '\', ']', '^', '_',
    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
    'x', 'y', 'z', '{', '|', '}', '~', DEL,
    C128, C129, C130, C131, C132, C133, C134, C135,
    C136, C137, C138, C139, C140, C141, C142, C143,
    C144, C145, C146, C147, C148, C149, C150, C151,
    C152, C153, C154, C155, C156, C157, C158, C159,
    ' ', '¡', '¢', '£', '¤', '¥', '¦', '§',
    '¨', '©', 'ª', '«', '¬', '­', '®', '¯',
    '°', '±', '²', '³', '´', 'µ', '¶', '·',
    '¸', '¹', 'º', '»', '¼', '½', '¾', '¿',
    'À', 'Á', 'Â', 'Ã', 'Ä', 'Å', 'Æ', 'Ç',
    'È', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï',
    'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', '×',
    'Ø', 'Ù', 'Ú', 'Û', 'Ü', 'Ý', 'Þ', 'ß',
    'à', 'á', 'â', 'ã', 'ä', 'å', 'æ', 'ç',
    'è', 'é', 'ê', 'ë', 'ì', 'í', 'î', 'ï',
    'ð', 'ñ', 'ò', 'ó', 'ô', 'õ', 'ö', '÷',
    'ø', 'ù', 'ú', 'û', 'ü', 'ý', 'þ', 'ÿ');
  type severity_level is (note, warning, error, failure);
--- Predefined numeric types:
  type integer is range -2147483647 to 2147483647; -- Limits defined by §5.2.3.1
  type real is range -1.0E308 to 1.0E308;
--- Predefined type TIME:
  type time is range -2147483647 to 2147483647
    units
      fs;             -- femtosecond
      ps = 1000 fs;   -- picosecond
      ns = 1000 ps;   -- nanosecond
      us = 1000 ns;   -- microsecond
      ms = 1000 us;   -- millisecond
      sec = 1000 ms;  -- second
      min = 60 sec;   -- minute
      hr = 60 min;    -- hour
    end units;
  subtype delay_length is time range 0 fs to time'high;
  impure function now return delay_length;
-- Predefined numeric subtypes:
  subtype natural is integer range 0 to integer'high;
  subtype positive is integer range 1 to integer'high;
-- Predefined array types:
  type string is array (positive range <>) of character;
  type boolean_vector is array (natural range <>) of boolean;
  type bit_vector is array (natural range <>) of bit;
  type integer_vector is array (natural range <>) of integer;
  type real_vector is array (natural range <>) of real;
  type time_vector is array (natural range <>) of time;
  type file_open_kind is (
    read_mode,        -- Resulting access mode is read-only.
    write_mode,       -- Resulting access mode is write-only.
    append_mode);     -- Resulting access mode is write-only;
                      -- information is appended to the end
                      -- of the existing file.
  type file_open_status is (
    open_ok,          -- File open was successful.
    status_error,     -- File object was already open.
    name_error,       -- External file not found or inaccessible.
    mode_error);      -- Could not open file with requested access mode.
  attribute foreign : string;
end standard;
