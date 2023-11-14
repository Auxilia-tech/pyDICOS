#!/bin/bash
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
host=dcs

# directory where ca-certificates are copied for installation
# should be /usr/local/share/ca-certificates on ubuntu
# should be /etc/pki/ca-trust/source/anchors/ on centos
ca_cert_dir="/usr/local/share/ca-certificates/" # ca_update_cmd for ubuntu
#ca_cert_dir="/etc/pki/ca-trust/source/anchors/" # ca_cert_dir for centos

# command to update the installed ca certificates
# should be "update-ca-certificates" on ubuntu
# should be "update-ca-trust ; update-ca-trust force-enable ; update-ca-trust extract ; cp /etc/ssl/certs/ca-bundle.crt /etc/ssl/certs/ca-certificates.crt" on centos
ca_update_cmd="update-ca-certificates" # ca_update_cmd for ubuntu
# ca_update_cmd="update-ca-trust ; update-ca-trust force-enable ; update-ca-trust extract ; cp /etc/ssl/certs/ca-bundle.crt /etc/ssl/certs/ca-certificates.crt" # ca_update_cmd for centos

# Create key pair for host
openssl genrsa -out $host.key 4096
openssl rsa -in $host.key -pubout -out $host.pubkey
 
# Create signing request
openssl req -new -key $host.key -out $host.csr -subj "/C=XX/ST=State/L=City/O=Org/CN=$host/emailAddress=example@example.com"
 
# Create key pair for host-test
openssl genrsa -out $host-test.key 4096
openssl rsa -in $host-test.key -pubout -out $host-test.pubkey
 
# Create signing request
openssl req -new -key $host-test.key -out $host-test.csr -subj "/C=XX/ST=State/L=City/O=Org/CN=$host/emailAddress=example@example.com"
#-config client_conf.conf -extensions sub_ca_ext
 
# Create CA key and cert
openssl genrsa -out ca11.key 4096
openssl req -new -x509 -key ca11.key -out ca11.crt -subj "/C=XX/ST=State/L=City/O=Org/CN=ca11.$host/emailAddress=example@example.com"
#-config client_conf.conf -extensions sub_ca_ext
 
# Install CA cert into OS
openssl x509 -in ca11.crt -out ca11.pem -outform PEM

cp ca11.pem $ca_cert_dir
cp ca11.crt $ca_cert_dir

$ca_update_cmd

# Create signed cert for host
openssl x509 -req -in $host.csr -CA ca11.crt -CAkey ca11.key -CAcreateserial -out $host.crt 
#-extfile client_conf.conf -extensions sub_ca_ext
 
# Create signed cert for host-test
openssl x509 -req -in $host-test.csr -CA ca11.crt -CAkey ca11.key -CAcreateserial -out $host-test.crt 
#-extfile client_conf.conf -extensions sub_ca_ext
 
# Create PFX files
openssl pkcs12 -export -out $host.pfx -inkey $host.key -in $host.crt
openssl pkcs12 -export -clcerts -out $host-test.pfx -inkey $host-test.key -in $host-test.crt
