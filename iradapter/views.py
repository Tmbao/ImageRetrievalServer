from django.http import HttpResponse, Http404
from django.shortcuts import render, get_object_or_404

from rest_framework import status
from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser, FileUploadParser
from rest_framework.response import Response
from rest_framework.views import APIView

from iradapter.models import RequestImage, ResponseRankedList
from iradapter.serializers import RequestImageSerializer, ResponseRankedListSerializer


class RequestList(APIView):
    """
    List all requests, or create a new request.
    """
    parser_classes = (JSONParser, FileUploadParser,)

    def get(self, request, format=None):
        requests = RequestImage.objects.all()
        serializer = RequestImageSerializer(requests, many=True)
        return Response(serializer.data, status.HTTP_200_OK)

    def post(self, request, format=None):
        image = RequestImage.objects.create(content=request.FILES['content'])
        ResponseRankedList.objects.create(request=image, status='P')

        serializer = RequestImageSerializer(image)
        return Response(serializer.data, status.HTTP_201_CREATED)


class ResponseLandscapeDetail(APIView):
    """
    Request detail, and ranked list
    """
    def get(self, request, pk, format=None):
        response = get_object_or_404(ResponseRankedList, pk=pk)
        serializer = ResponseRankedListSerializer(response)
        return Response(serializer.data, status.HTTP_200_OK)
