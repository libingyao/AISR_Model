# AISR_Model
Astronomical image data management and subsets retrieval min-cost-model in the cloud

# Dependency
* mysql-client (which depends on openssl)
* CFITSIO (which depends on curl)

# Setup
1. Please intall the above libs
2. create a new file, named as `Makefile.rule`, in this project's root dir
3. establish the following path vars in Makefile.rule, according to your local settings

## Example Makefile.rule
MYSQLCLIENT_DIR = /usr/local/opt/mysql-client

OPENSSL_DIR     = /usr/local/opt/openssl

CURL_DIR        = /usr/local/opt/curl

CFITSIO         = common/cfitsio
