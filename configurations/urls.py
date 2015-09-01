from django.conf.urls import patterns, include, url
from django.contrib import admin

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'IRRESTServer.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^admin/', include(admin.site.urls)),
    url(r'^retrieve/', include('iradapter.urls', namespace='iradapter')),
    url(r'^landscapes/', include('landscapes.urls', namespace='landscapes'))
)
