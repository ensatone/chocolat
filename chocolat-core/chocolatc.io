f := File with("main.chocolat")
f openForReading
text := f readToEnd
text := text split("\n") join(";")
text := "#{text} " interpolate
text := text asList
tokens := List clone
token := ""
tok := Object clone
tok plus := "TOK_PLUS"
tok minus := "TOK_MINUS"
tok multiply := "TOK_MULTIPLY"
tok power := "TOK_POWER"
tok divide := "TOK_DIVIDE"
tok comma := "TOK_COMMA"
tok equal := "TOK_EQUAL"
tok equalto := "TOK_EQUALTO"
tok inequalto := "TOK_INEQUALTO"
tok greaterthan := "TOK_GREATERTHAN"
tok lessthan := "TOK_LESSTHAN"
tok slash := "TOK_SLASH"
tok greaterthanequalto := "TOK_GREATERTHANEQUALTO"
tok lessthanequalto := "TOK_LESSTHANEQUALTO"
tok class := "TOK_CLASS"
tok AND := "TOK_AND"
tok OR := "TOK_OR"
tok OBJ := "TOK_OBJ"
tok ASCII := "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_:" asList
tok ppt := 0
tok parencount := 0
tok lparencount := 0
tok rparencount := 0
output_codes := ""
currentclass := ""
setclass := false
registration := List clone
reg_return := false
reg_class := ""
reg_mode := ""
pcounts := 0
registers := 0
parameters := 0
reregisters := 0
compilecase := List clone
compilemax := 0
string_s := 0
string_f := 0
tok isnumber := method(x,
return x == "1" or x == "2" or x == "3" or x == "4" or x == "5" or x == "6" or x == "7" or x == "8" or x == "9" or x == "0" or x == "."
)
tok isASCII := method (y,
result := false
for (c,0,tok ASCII size - 1, 1,
if (tok ASCII at(c) == y) then (
    result := true
)
)
return result
)
for (x,0,text size-1,1,
if (tok isnumber(text at(x))) then (
for (y,x,text size-1,1,
 if (tok isnumber(text at(y))) then (
 token := "#{token}#{text at(y)}" interpolate
 text atPut(y,"")
 ) else (
  tokens append(token)
  token := ""
  break
 )
)
) elseif (text at(x) == "\"") then (
    token := "#{token}\"" interpolate
    string_s = x
    for (y,x+1,text size - 1,1,
    if (text at(y) == "\\") then (
        if (text at(y+1) == "\\" or text at(y+1) == "\"" or text at(y+1) == "n") then (
            if (text at(y+1) == "n") then (
                token := "#{token}\\" interpolate
            )
            token := "#{token}#{text at(y+1)}" interpolate
            text atPut(y+1,"")
        ) else (
            continue
        )
    ) elseif (text at(y) == "\"") then (
        if (text at(y-1) == "\\") then (
           continue
           ) else (
            tokens append(token)
            token := ""
            string_f = y
            break
        )
    ) else (
        token := "#{token}#{text at(y)}" interpolate
        )
    )
for (j,string_s,string_f,1,
     text atPut(j,"")
)
) elseif (text at(x) == "@") then (
    tokens append(tok class)
) elseif (text at(x) == "#") then (
    if (text at(x-1) != "\\") then (
    tokens append(tok slash)
    )
) elseif (text at(x) == "+") then (
tokens append(tok plus)
) elseif (text at(x) == "-") then (
if (tokens at(tokens size - 1) == "(") then (
    tokens append("0")
)
tokens append(tok minus)
) elseif (text at(x) == "*") then (
tokens append(tok multiply)
) elseif (text at(x) == "/") then (
tokens append(tok divide)
) elseif (text at(x) == "{") then (
   tokens append("(")
   tokens append("#setlist") 
   if (text at(x+1) == "}") then (
       tokens append("null")
   )
) elseif (text at(x) == "}") then (
    tokens append(")")
) elseif (text at(x) == "(") then (
tokens append("(")
) elseif (text at(x) == ")") then (
tokens append(")")
) elseif (text at(x) == "[") then (
    tokens append("(")
        tokens append("#sys")
) elseif (text at(x) == "]") then (
    tokens append(")")
) elseif (text at(x) == "^") then (
    tokens append(tok power)
) elseif (text at(x) == ",") then (
    tokens append(tok comma)
) elseif (text at(x) == "==") then (
    tokens append(tok equalto)
) elseif (text at(x) == ">") then (
    if (text at(x+1) == "=") then (
        tokens append(tok greaterthanequalto)
        text atPut(x+1,"")
    ) else (
        tokens append(tok greaterthan)
    )
) elseif (text at(x) == "<") then (
    if (text at(x+1) == "=") then (
        tokens append(tok lessthanequalto)
        text atPut(x+1,"")
    ) else (
        tokens append(tok lessthan)
    )
) elseif (text at(x) == "=") then (
    if (text at(x+1) == "=") then (
        tokens append(tok equalto)
        text atPut(x+1,"")
    ) elseif (text at(x-1) == "!") then (
        tokens append(tok inequalto)
    ) else (
        tokens append(tok equal)
    )
) elseif (tok isASCII(text at(x))) then (
for (a,x, text size - 1,1,
if (tok isASCII(text at(a)) or tok isnumber(text at(a))) then (
    token := "#{token}#{text at(a)}" interpolate
    text atPut(a,"")
) elseif (token == "and" or token == "or" or token == "obj") then ( 
if (token == "and") then (
    tokens append(tok AND)
) elseif (token == "or") then (
    tokens append(tok OR)
) elseif (token == "obj") then (
    tokens append(tok OBJ)
)
    token := ""
    break
) elseif (text at(a) == "{") then (
    token := "#{token}" interpolate
    tokens append("(")
    tokens append("#getlist")
    tokens append(token)
    tokens append(tok comma)
    text atPut(a,"")
    token := ""
    break
) elseif (text at(a) == "(") then (
    token := "##{token}" interpolate
    tokens append("(")
    tokens append(token)
    text atPut(a,"")
    token := ""
    if (text at(a+1) == ")") then (
        tokens append("1")
    )
    break
) elseif (text at(a) == " ") then (
    continue
) else (
    tokens append(token)
    token := ""
    break
)
)
)
)
without_comments := List clone
token_number := 0
while (token_number < tokens size,
if (tokens at(token_number) == tok slash) then (
    for (token_number_skip,token_number + 1,tokens size - 1,1,
    if (tokens at(token_number_skip) == tok slash) then (
        token_number := token_number_skip
        break
    )
    )
) else (
    without_comments append(tokens at(token_number))
)
token_number := token_number + 1
)
tokens := without_comments
without_comments := List clone
parse := method(expr,
tok ppt := tokens size - 1
while (tok ppt>0,
tok ppt := tok ppt - 1
if (tokens at(tok ppt) == expr) then (
    if (tokens at(tok ppt-1) == ")") then (
    for (p,tok ppt-1,0,-1,
     if (tokens at(p)==")") then (
         tok lparencount := tok lparencount + 1
     ) elseif (tokens at(p)=="(") then (
         tok lparencount := tok lparencount - 1
         if (tok lparencount == 0) then (
             tokens atInsert(p,"(")
             break
         )
     )
    )
    ) else (
        tokens atInsert(tok ppt-1,"(")
    ) 
    
    if (tokens at(tok ppt+2) == "(") then (
    for (pr,tok ppt+2,tokens size-1,1,
     if (tokens at(pr)=="(") then (
         tok rparencount := tok rparencount + 1
     ) elseif (tokens at(pr)==")") then (
         tok rparencount := tok rparencount - 1
         if (tok rparencount == 0) then (
             tokens atInsert(pr+1,")")
             break
         )
     )
    )
    )else(
        tokens atInsert(tok ppt+3,")")
    )
)
    
)
tok ppt := 0
)
parse(tok power)
parse(tok multiply)
parse(tok divide)
parse(tok minus)
parse(tok plus)
parse(tok equalto)
parse(tok inequalto)
parse(tok greaterthan)
parse(tok greaterthanequalto)
parse(tok lessthan)
parse(tok lessthanequalto)
parse(tok AND)
parse(tok OR)
parse(tok equal)
reg := method(variable_name,variable,
if (variable_name asList at(0) == ":") then (
    variable_name := variable_name exSlice(1,variable_name asList size)
    variable_name := ".#{variable_name}" interpolate
)
    if (tok isnumber(variable asList at(0))) then (
        output_codes := "#{output_codes} svs _#{variable_name} _#{variable} svf " interpolate
        return output_codes
    ) elseif (variable asList at(0) == "\"") then (
output_string := variable exSlice(1,variable asList size) asList
out_str := ""
for (i,0,output_string size-1,1,
if (output_string at(i) == " ") then (
    out_str := "#{out_str} _" interpolate
) else (
    out_str := "#{out_str}#{output_string at(i)}" interpolate
)
)
output_string := out_str
    output_codes := "#{output_codes} svs _#{variable_name} _#{output_string} svf " interpolate
    return output_codes
    ) elseif (tok isASCII(variable asList at(0))) then (
    if (variable asList at(0) == ":") then (
    variable := variable exSlice(1,variable asList size)
    variable := ".#{variable}" interpolate
    )
        output_codes := "#{output_codes} cv _#{variable_name} _#{variable} " interpolate
        return output_codes
    ) else (
        return output_codes
    )
)
for (c,0, tokens size - 1,1,
if (tokens at(c) == "(") then (
    tok parencount := tok parencount + 1
compilecase append("(")
    compilemax := compilemax + 1
) elseif (tokens at(c) == ")") then (
tok parencount := tok parencount - 1
    compilecase append(")")
    compilecase append("$#")

) else (
compilecase append(tokens at(c))
    
)
if (tok parencount == 0) then (
for (cc,compilemax,0,-1,
for (ccc,0, compilecase size - 1,1,
if (compilecase at(ccc) == "(") then (
tok parencount := tok parencount + 1
    
) elseif (compilecase at(ccc) == ")") then (
    tok parencount := tok parencount - 1
) else (
    if (tok parencount == cc) then (
    if (compilecase at(ccc) == "$#") then (
    reregisters := reregisters + 1
        registration append("R#{reregisters}" interpolate)
    ) else (
        registration append(compilecase at(ccc))
        )
    )
)

)
if (cc == 0) then (
reregisters = 0
    registration append("&&")
)

)

compilemax := 0
compilecase := List clone
)
)

reparse := method (tok_name,
count := registration size
while (count > 0,
count := count - 1
if (registration at(count) == tok_name) then (
if (tok_name == tok class) then (
        registration atInsert(count,"(")
        if (registration at(count+4) != nil) then (
    registration atInsert(count+4,")")
    ) else (
        registration atInsert(count+3,")")
    )
)else (
    registration atInsert(count-1,"(")
    registration atInsert(count+3,")")
    )
)
)
)
reparse(tok class)
reparse(tok power)
reparse(tok multiply)
reparse(tok divide)
reparse(tok plus)
reparse(tok minus)
reparse(tok equalto)
reparse(tok inequalto)
reparse(tok greaterthan)
reparse(tok greaterthanequalto)
reparse(tok lessthan)
reparse(tok lessthanequalto)
reparse(tok AND)
reparse(tok OR)
reparse(tok equal)

for (r,0,registration size - 1,1,
if (registration at(r) == "(") then (
    tok parencount := tok parencount + 1
    continue
) elseif (registration at(r) == ")") then (
    tok parencount := tok parencount - 1
    continue
)
if (tok parencount == 1) then (
 if (registration at(r) == tok class) then (
     if (setclass == false) then (
     currentclass := registration at(r+2)
         setclass := true
     ) else (
                wf := File with("#{currentclass}.ccl" interpolate)
           wf remove
           wf openForUpdating 
           wf write (output_codes)
           output_codes := ""
           wf close()
     currentclass := ""
         setclass := false
     )
 ) elseif (registration at(r) == tok power) then (
     output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     register := "R#{registers}" interpolate
     output_codes := reg(register,"0")
     output_codes := "#{output_codes} m+ _#{register} _v1 " interpolate
     output_codes := "#{output_codes} m^ _#{register} _v2 " interpolate
     
 ) elseif (registration at(r) == tok multiply) then (
     output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     register := "R#{registers}" interpolate
     output_codes := reg(register,"0")
     output_codes := "#{output_codes} m+ _#{register} _v1 " interpolate
     output_codes := "#{output_codes} m* _#{register} _v2 " interpolate
 ) elseif (registration at(r) == tok divide) then (
     output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     register := "R#{registers}" interpolate
     output_codes := reg(register,"0")
     output_codes := "#{output_codes} m+ _#{register} _v1 " interpolate
     output_codes := "#{output_codes} m/ _#{register} _v2 " interpolate
 ) elseif (registration at(r) == tok plus) then (
     output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     register := "R#{registers}" interpolate
     output_codes := reg(register,"0")
     output_codes := "#{output_codes} m+ _#{register} _v1 " interpolate
     output_codes := "#{output_codes} m+ _#{register} _v2 " interpolate
 ) elseif (registration at(r) == tok minus) then (
     output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     register := "R#{registers}" interpolate
     output_codes := reg(register,"0")
     output_codes := "#{output_codes} m+ _#{register} _v1 " interpolate
     output_codes := "#{output_codes} m- _#{register} _v2 " interpolate
 ) elseif (registration at(r) == tok equal) then (
     output_codes := reg(registration at(r-1), registration at(r+1))
 ) elseif (registration at(r) == tok equalto) then (
      output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     output_codes := "#{output_codes} m== _R#{registers} _v1 _v2 " interpolate
 ) elseif (registration at(r) == tok inequalto) then (
     output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     output_codes := "#{output_codes} m!= _R#{registers} _v1 _v2 " interpolate
 ) elseif (registration at(r) == tok lessthanequalto) then (
      output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     output_codes := "#{output_codes} m<= _R#{registers} _v1 _v2 " interpolate
 ) elseif (registration at(r) == tok greaterthanequalto) then (
      output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     output_codes := "#{output_codes} m>= _R#{registers} _v1 _v2 " interpolate
 ) elseif (registration at(r) == tok lessthan) then (
      output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     output_codes := "#{output_codes} m< _R#{registers} _v1 _v2 " interpolate
 ) elseif (registration at(r) == tok greaterthan) then (
      output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     output_codes := "#{output_codes} m> _R#{registers} _v1 _v2 " interpolate
 ) elseif (registration at(r) == tok AND) then (
      output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     output_codes := "#{output_codes} m& _R#{registers} _v1 _v2 " interpolate
 ) elseif (registration at(r) == tok OR) then (
      output_codes := reg("v1",registration at(r-1))
     output_codes := reg("v2",registration at(r+1))
     registers := registers + 1
     output_codes := "#{output_codes} m| _R#{registers} _v1 _v2 " interpolate
 )
) else (
 if (registration at(r) == "&&") then (
 reg_return := false
     registers := 0
     for (rr, r+1, registration size - 1,1,
         if (registration at(rr) == "#elif") then (
             output_codes := "#{output_codes} endif " interpolate
         ) elseif (registration at(rr) == "#while") then (
             output_codes := "#{output_codes} startw " interpolate
         ) elseif (registration at(rr) == "&&") then (
             break
         )
     )
 ) elseif (registration at(r) == "#while") then (
     output_codes := "#{output_codes} while _#{registration at(r+1)} " interpolate
 ) elseif (registration at(r) == "#if") then (
     output_codes := "#{output_codes} if _#{registration at(r+1)} " interpolate
 ) elseif (registration at(r) == "end") then (
     output_codes := "#{output_codes} endif " interpolate
 ) elseif (registration at(r) == "endf") then (
     output_codes := "#{output_codes} endf endff " interpolate
 ) elseif (registration at(r) == "endw") then (
     output_codes := "#{output_codes} endw " interpolate
 ) elseif (registration at(r) == "#elif") then (
     output_codes := "#{output_codes} elf _#{registration at(r+1)} " interpolate 
 ) elseif (registration at(r) == "else") then (
     output_codes := "#{output_codes} endif " interpolate
     output_codes := "#{output_codes} els " interpolate
 ) elseif (registration at(r) == "break") then (
     output_codes := "#{output_codes} bk " interpolate
 ) elseif (registration at(r) == "continue") then (
     output_codes := "#{output_codes} endf ctn " interpolate
 ) elseif (registration at(r) == tok OBJ) then (
     output_codes := "#{output_codes} obj _#{registration at(r+2)} " interpolate
 )  elseif (registration at(r) asList at(0) == "#") then (
 reg_return := true
 reg_class := registration at(r)
 reg_class := reg_class exSlice(1,reg_class asList size)
 reg_mode := "callingfunc"
 )    else (
     if (reg_mode == "callingfunc") then (
     if (registration at(r) == tok comma) then (
         continue
     ) elseif (registration at(r+1) == tok comma) then (
     pcounts := pcounts + 1
          if (reg_class == "sys") then (
           output_codes := reg("r#{pcounts}" interpolate,registration at(r))
          ) elseif (reg_class == "for") then (
              if (pcounts == 1) then (
               output_codes := "#{output_codes} svs _r1 _#{registration at(r)} svf " interpolate
              ) else ( 
               output_codes := reg("r#{pcounts}" interpolate,registration at(r))
              )
          ) elseif (reg_class == "setlist") then (
              if (pcounts == 1) then (
                  output_codes := "#{output_codes} lm " interpolate
              )
              output_codes := reg("l#{pcounts}" interpolate,registration at(r))
          ) elseif (reg_class == "getlist") then (
                  output_codes := reg("g#{pcounts}" interpolate,registration at(r))
          ) else (
           output_codes := reg("p#{pcounts}" interpolate,registration at(r))
           )
       ) else (
       pcounts := pcounts + 1
registers := registers + 1
       if (reg_class == "sys") then (
       output_codes := "#{output_codes} #{registration at(r)} " interpolate
       if (registration at(r) == "append" or registration at(r) == "put" or registration at(r) == "addstr") then (
           output_codes := "#{output_codes} #{pcounts} " interpolate
       )
       ) elseif (reg_class == "setlist") then (
           output_codes := reg("l#{pcounts}" interpolate,registration at(r))
           output_codes := "#{output_codes} list #{pcounts} " interpolate
       ) elseif (reg_class == "for") then (
                                output_codes := reg("r#{pcounts}" interpolate,registration at(r))
                                output_codes := "#{output_codes} for " interpolate
       ) elseif (reg_class == "getlist") then (
           output_codes := reg("g#{pcounts}" interpolate,registration at(r))
           output_codes := "#{output_codes} glist #{pcounts} " interpolate
       ) else (
                                output_codes := reg("p#{pcounts}" interpolate,registration at(r))
                  output_codes := "#{output_codes} rd #{reg_class}.ccl " interpolate
       )
        if (reg_return == true and reg_class != "for") then (
     output_codes := reg("R#{registers}" interpolate,"return")
        )
       reg_mode := ""
       pcounts := 0
       )
     ) else (
     registers := registers + 1
     output_codes := reg("R#{registers}" interpolate,registration at(r))
     )
 )

)

)
