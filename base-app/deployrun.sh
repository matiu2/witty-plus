#!/bin/sh
./${EXE_NAME} --docroot="static-content;/resources" --deploy-path="/" --http-address=0.0.0.0 --http-port=80 -c wt-config.xml

