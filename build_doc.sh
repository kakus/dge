#! /bin/bash

echo Making scritpt documentation
yuidoc -C -o scripts_doc/ -e .api,.js scripts
