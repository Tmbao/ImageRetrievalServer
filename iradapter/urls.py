from django.conf.urls import url
from iradapter.views import RequestList, RequestDetail


urlpatterns = [
    url(r'^request$', RequestList.as_view()),
    url(r'^request/(?P<pk>[0-9]+)/$', RequestDetail.as_view()),
]
