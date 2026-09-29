curl -x "http://172.31.2.3:8080/" \
  "https://generativelanguage.googleapis.com/v1beta/models/gemini-3.8-flash:generateContent" \
  -H "x-goog-api-key: AQ.Ab8RN6IiYytnHtCdcGdmSsubGyKJ0wutzmfhTQzNMk4rq7j5BA" \
  -H "Content-Type: application/json" \
  -d '{
    "contents": [
      {
        "parts": [
          {
            "text": "Hello!"
          }
        ]
      }
    ]
  }'
