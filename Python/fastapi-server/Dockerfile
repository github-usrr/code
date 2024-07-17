# To run the container:
# docker build . --tag fastapi-server && docker run -p 80:80 fastapi-server

FROM python:3.11-slim

WORKDIR /usr/src/app
COPY . .
RUN pip install -r requirements.txt

ARG PORT=80
EXPOSE $PORT
CMD uvicorn main:app --host 0.0.0.0 --port $PORT --reload
