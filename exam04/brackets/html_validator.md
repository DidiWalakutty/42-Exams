Assignment name  : html_validator
Expected files   : *.c
Allowed functions: write, malloc, free, strncpy, strcmp
--------------------------------------------------------------------------------

You do not need to understand HTML for this assignment.
Write a function that takes one string.
It returns 0 if the string is a valid HTML-string, and 1 if it's faulty.
If no arguments, return 1.

<test> is an openingstag.
</test> is a closing tag.

examples:
1. <test> </test>
	is correct
2. <test>
		<second_tag_name>
			<third_tag_name some_attribute"One Ring!">
			</third_tag_name>
		</second_tag_name>
	</test>
	is correct
3. <test>
		<second_tag_name>
			<third>
		</second_tag_name>
	</test>
	is incorrect (not closing third)

<img> is an exception and selfclosing. It has no content 
and is closed immediately.

An opening tag must always be closed by the corresponding closing tag in
the correct order.
A string that does not contain any tag is considered as a correctly formatted string.