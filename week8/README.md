# Week 8 - HTML, CSS, & JavaScript

## Welcome!
- In previous weeks, we introduced you to Python, a high-level programming language that utilized the same building blocks we learned in C. Today, we will extend those building blocks further in HTML, CSS, and JavaScript.
- The internet is a technology that we all use.
- Using our skills from previous weeks, we can build our own web pages and applications.
- The ARPANET connected the first points on the internet to one another.
- Dots between two points could be considered routers.

## Routers
- To route data from one place to another, we need to make routing decisions. That is, someone needs to program how data is transfered from point A to point B.
- You can imagine how data could take multiple paths from point A and point B, such that when a router is congested, data can flow through another path.
- TCP/IP are two protocols that allow computers to transfer data between them over the internet.
- IP or internet protocol is a way by which computers can identify one another across the internet. Every computer has a unique address in the world. Addresses are in this form:

  `#.#.#.#`
- Numbers range from 0 to 255. IP addresses are 32-bits, meaning that these addresses could accommodate over 4 billion addresses. Newer versions of IP addresses can accommodate far more computers!
- In the real world, servers do a lot of work for us.
- TCP, or transmission control protocol, is used to distinguish web services from one another. For example, 80 is used to denote HTTP and 443 is used to denote HTTPS. These numbers are port numbers.
- When information is sent from one location to another, an IP address and TCP port number are sent.
- These protocols are also used to fragment large files into multiple parts called packets. For example, a large photo of a cat can be sent in multiple packets. When a packet is lost, TCP/IP can request missing packets again from the origin server.
- TCP will acknowledge when all the data has been transmitted and received.

## DNS
- It would be very tedious if you needed to remember an address number to visit a website.
- DNS, or domain name systems, is a collection of servers on the internet that are used to route website addresses like harvard.edu to a specific IP address.
- DNS simply hold a table or database that links specific, fully qualified domain names to specific IP addresses.

## HTTP
- HTTP or hypertext transfer protocol is an application-level protocol that developers use to build powerful and useful things.
- When you see an address such as https://www.example.com you are actually implicitly visiting that address with a / at the end of it.
- The path is what exists after that slash. For example, https://www.example.com/folder/file.html visits example.com and browses to the folder folder and then visits the file named file.html.
- https in this address is the protocol that is used to connect to that web address. By protocol, we mean that HTTP utilizes GET or POST requests to ask for information from a server. For example, you can launch Google Chrome, right-click, and click inspect. When you open the developer tools and visit Network, selecting Preserve log, you will see Request Headers. You’ll see mentions of GET. This is possible in other browsers as well, using slightly different methods.
- Generally, after making a request a server, you will receive the following in Response Headers:
```
 HTTP/1.1 200 OK
  Content-Type: text/html
```
- This approach to inspecting these logs may be a bit more complicated than need be. You can analyze the work of HTTP protocols at code.cs50.io. For example, type the following in your terminal window:
```
curl -I https://www.harvard.edu
```
Notice that the output of this command returns all the header values of the responses of the server.
- Similarly, execute the following in your terminal window:
```
  curl -I http://www.harvard.edu
```
Notice that the s in https has been removed. The server response will show that the response is 301 instead of 100, meaning that the website has permanently moved.
- Further, execute the following command in your terminal window:
```
 curl -I https://harvard.edu
```
Notice that you will see the same 301 response, providing a hint to a browser of where it can find the correct website.
- Similar to 301, a code of 404 means that a specified URL has not been found. There are numerous other response codes, such as:
```
  200 OK
  301 Moved Permanently
  302 Found
  304 Not Modified
  304 Temporary Redirect
  401 Unauthorized
  403 Forbidden
  404 Not Found
  418 I'm a Teapot
  500 Internal Server Error
  503 Service Unavailable
```
- It’s worth mentioning that 500 errors are always your fault as the developer. This will be especially important for next week’s pset, and potentially for your final project!
- We can send more complicated commands to the server. For example, we can attempt the following:
```
 GET /search?q=cats HTTP/1.1
 Host: www.google.com
```
Notice that not only are we specifying a path but also user input using the ? mark. q is used to denote query, passing cats to it.
- If you manually type google.com/search?=cats into your web browser address bar, it will manually query Google for results related to cats.

## HTML
