#!/usr/bin/env bash

id=$(mmsg get focusing-client | jq -r ".id")

mmsg dispatch togglefloating
mmsg dispatch resizewin,1214,868 client,$(id)
mmsg dispatch centerwin