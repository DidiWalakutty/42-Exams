Assignment name  : html_validator<br>
Expected files   : *.c<br>
Allowed functions: write, malloc, free, strncpy, strncmp<br>
--------------------------------------------------------------------------------

You do not need to understand HTML for this assignment.<br>
Write a function that takes one string.<br>
It returns 0 if the string is a valid HTML-string, and 1 if it's faulty.<br>
If no arguments, return 1.<br>

`<test>` is an openingstag.<br>
`</test>` is a closing tag.<br>

examples:
1. `<test>` `</test>`<br>
    is correct<br>
2. `<test>`<br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`<second_tag_name>`<br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`<third_tag_name some_attribute"One Ring!">`<br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`</third_tag_name>`<br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`</second_tag_name>`<br>
   `</test>`<br>
   is correct<br>

3.`<test>`<br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`<second_tag_name>`<br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`<third>`<br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`</second_tag_name>`<br>
`</test>`<br>
	is incorrect (not closing third)<br>

`<img>` is an exception and selfclosing. It has no content 
and is closed immediately.

An opening tag must always be closed by the corresponding closing tag in
the correct order.
A string that does not contain any tag is considered as a correctly formatted string.
