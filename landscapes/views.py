from django.http import HttpResponse, Http404
from django.shortcuts import render, get_object_or_404

from rest_framework import status
from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser, FileUploadParser
from rest_framework.response import Response
from rest_framework.views import APIView

from landscapes.models import Landscape, LandscapeResource
from landscapes.serializers import LandscapeSerializer, LandscapeResourceSerializer


class LandscapeList(APIView):
    """
    List all requests, or create a new request.
    """
    parser_classes = (JSONParser, FileUploadParser,)

    def get(self, request, format=None):
        landscapes = Landscape.objects.all()
        serializer = LandscapeSerializer(landscapes, many=True)
        return Response(serializer.data, status.HTTP_200_OK)


class LandscapeDetail(APIView):
    """
    Request detail, and ranked list
    """
    def get(self, request, pk, format=None):
        landscape = get_object_or_404(Landscape, pk=pk)
        serializer = LandscapeSerializer(landscape)
        return Response(serializer.data, status.HTTP_200_OK)
