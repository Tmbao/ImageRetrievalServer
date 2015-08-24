from django.conf.urls import url
from landscapes.views import LandscapeList, LandscapeDetail


urlpatterns = [
    url(r'^landscapes$', LandscapeList.as_view()),
    url(r'^landscape/(?P<pk>[0-9]+)/$', LandscapeDetail.as_view()),
]
