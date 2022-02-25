# Program for client part
[Server part](https://github.com/V31R/Server) 
## app.settings file
To run this program correctly at the current moment you have to add `app.settings` file.
This files must contatins information about port, ip address for UDP socket.
Tha base structure of file is:
    `<name_of_property>value_of_property</name_of_property>`
This scheme looks like tags :).
Available property:
- `port` - positive number of port (default value = ?)
- `address` - string with ipv4 address (default value = ?)
- `name` - name of current profile settings