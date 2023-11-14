#!/usr/bin/bash
##############################################################################
### Stratovan Corporation Copyright and Disclaimer Notice:
###
### Copyright (c) 2021 Stratovan Corporation. All Rights Reserved.
###
### Permission to use, copy, modify, and distribute this software and its
### documentation without a signed licensing agreement, is hereby granted,
### provided that this copyright notice, this paragraph and the following two
### paragraphs appear in all copies, modifications, and distributions.
###
### IN NO EVENT SHALL STRATOVAN BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
### SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
### ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
### STRATOVAN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
###
### STRATOVAN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
### TO, THE IMPLIED WARRANTIES OF USE AND FITNESS FOR A PARTICULAR PURPOSE. THE
### SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
### PROVIDED "AS IS". STRATOVAN HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
### SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS UNLESS DIRECTED BY THE
### U.S. GOVERNMENT'S TRANSPORTATION SECURITY ADMINISTRATION (TSA).
###
##############################################################################
set -e
set -x

# 
# Create key pair for Dicos server
#
openssl genrsa -out dicos_server.key 2048
openssl rsa -in dicos_server.key -pubout -out dicos_server.pubkey
 
# 
# Create signing request.
# Certificate subject information for server and client must match
#
openssl req -new -key dicos_server.key -out dicos_server.csr -subj "/C=XX/ST=State/L=City/O=Org/CN=dcs/emailAddress=example@example.com"
 
# 
# Create key pair for Dicos Client
#
openssl genrsa -out dicos_client.key 2048
openssl rsa -in dicos_client.key -pubout -out dicos_client.pubkey
 
# 
# Create signing request
# Certificate subject information for server and client must match
#
openssl req -new -key dicos_client.key -out dicos_client.csr -subj "/C=XX/ST=State/L=City/O=Org/CN=dcs/emailAddress=example@example.com" 

#
# Create signed cert for Dicos Server
#
openssl x509 -req -in dicos_server.csr -signkey dicos_server.key -out dicos_server.crt 
 
# 
# Create signed cert for Dicos Client
#
openssl x509 -req -in dicos_client.csr -signkey dicos_client.key -out dicos_client.crt 

# 
# Create PFX files
#
openssl pkcs12 -export -out dicos_server.pfx -inkey dicos_server.key -in dicos_server.crt
openssl pkcs12 -export -clcerts -out dicos_client.pfx -inkey dicos_client.key -in dicos_client.crt
