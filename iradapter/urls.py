from django.conf.urls import url
from iradapter.views import RequestList, ResponseLandscapeDetail


urlpatterns = [
    url(r'^requests$', RequestList.as_view()),
    url(r'^response/landscape/(?P<pk>[0-9]+)/$', ResponseLandscapeDetail.as_view()),
]
